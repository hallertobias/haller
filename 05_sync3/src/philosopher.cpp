/*
    author: Haller Tobias
    class: 5AHIF
*/

#include <iostream>
#include "philosopher.h"
#include <mutex>
#include "semaphoreOwn.h"

using namespace std;

recursive_mutex out_mtx;

void println() {
    lock_guard<recursive_mutex> lg{out_mtx};
    cout << endl;
}

template<typename T, typename... Rest>
void println(const T& word, const Rest&... rest) {
    lock_guard<recursive_mutex> lg{out_mtx};
    cout << word << ' ';
    println(rest...);
}

void Philosopher::operator()(SemaphoreOwn* s, bool livelock) {
    while (true){
        println("Philosopher", id, "is thinking...");
        this_thread::sleep_for(1s);

        println("Philosopher", id, "attempts to get left fork");
        if(s != nullptr){
            s->acquire();
        }
        leftFork.lock();
        println("Philosopher", id, "got left fork. Now he wants the right one...");

        this_thread::sleep_for(5s);

        println("Philosopher", id, "attempts to get right fork");
        if (livelock){
            while(!rightFork.try_lock_for(chrono::seconds(3))) {
                this_thread::sleep_for(100ms);

                if (s != nullptr) {
                    s->release();
                }

                leftFork.unlock();
                println("Philosopher", id, "released left fork due to timeout getting the right one!");
            }
            this_thread::sleep_for(3s);
            continue;
        } else {
            rightFork.lock();
        }

        println("Philosopher", id, "got right fork. Now he is eating...");
        this_thread::sleep_for(2s);
        println("Philosopher", id, "finished eating");

        if(s != nullptr){
            s->release();
        }
        leftFork.unlock();
        println("Philosopher", id, "released left fork");
        println("currently", s->available_permits(), "left forks available");
        rightFork.unlock();
        println("Philosopher", id, "released right fork");
    }
};
