/*
    author: Haller Tobias
    class: 5AHIF
*/

#pragma once

#include <mutex>
#include <atomic>
#include <condition_variable>

class Semaphore{
    private:
        int cnr;
        std::mutex mtx;
        std::condition_variable wcv;
    public:
        Semaphore() : cnr{0}{};
        Semaphore(int size) : cnr{size}{};
        void acquire();
        void release();
        int available_permits();
}; 