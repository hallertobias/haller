
#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Pipe {
    std::queue<T> backend;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};

    public:
        Pipe& operator<<(T value) {
            if(!closed) {
                std::unique_lock<std::mutex> lock{mtx};
                backend.push(value);
                not_empty.notify_one();
            }
            return *this;
        }

        Pipe& operator>>(T& value) {
            if(!closed) {
                std::unique_lock<std::mutex> lock{mtx};
                not_empty.wait(lock, [this]{return backend.size();});
                backend.front();
                value = backend.pop();
            }
            return *this;
        }

        void close() {
            closed = true;
        }

        explicit operator bool() {
            return !closed;
        }
};