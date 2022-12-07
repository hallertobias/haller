/*
    author: Haller Tobias
    class: 5AHIF
*/

#pragma once

#include <thread>
#include <mutex>
#include "semaphoreOwn.h"

using namespace std;

class Philosopher {
    private: 
        int id; 
        timed_mutex& leftFork; 
        timed_mutex& rightFork;
    public:
        Philosopher(int id, timed_mutex& leftFork, timed_mutex& rightFork) : 
          id(id),
          leftFork(leftFork),
          rightFork(rightFork)
          {};
        void operator()(SemaphoreOwn* s, bool livelock);
};