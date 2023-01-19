
#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>

template <typename T>
class Pipe {
    std::queue<T> backend;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};
    long latency{0};

    public:
        Pipe& operator<<(T value) {
            future<void> future{async([&] {
                if (this->latency) {
                    this_thread::sleep_for(chrono::milliseconds(this->latency));
                }
                lock_guard<mutex> lock(mtx);
                backend.push(value);
                not_empty.notify_one();
            })};
            future.wait();
            return *this;
        }

        Pipe& operator>>(T& value) {
            if(!closed) {
                std::unique_lock<std::mutex> lock{mtx};
                not_empty.wait(lock, [this]{return backend.size();});
                backend.front();
                value = backend.front();
                backend.pop();
            }
            return *this;
        }

        void close() {
            closed = true;
        }

        explicit operator bool() {
            return !closed;
        }

        void set_latency(long latency) {
            this->latency = latency;
        }
};