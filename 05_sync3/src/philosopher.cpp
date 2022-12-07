/*
    author: Haller Tobias
    class: 5AHIF
*/

#include <iostream>
#include "philosopher.h"
#include <mutex>

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

void Philosopher::operator()() {
    while(true){
        println("Philosopher ", id, " is thinking...");
        this_thread::sleep_for(1s);

        println("Philosopher ", id, " attempts to get left fork");
        leftFork.lock();

        println("Philosopher ", id, " got left fork. Now he wants the right one... ");
        println("Philosopher ", id, " attempts to get right fork");
        rightFork.lock();

        println("Philosopher ", id, " got right fork. Now he is eating...");
        this_thread::sleep_for(2s);

        println("Philosopher ", id, " finished eating");
        println("Philosopher ", id, " released left fork");
        leftFork.unlock();
        println("Philosopher ", id, " released right fork");;
        rightFork.unlock();
    }
};
