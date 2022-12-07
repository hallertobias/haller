/*
    author: Haller Tobias
    class: 5AHIF
*/

#pragma once

#include <mutex>
#include <atomic>
#include <condition_variable>

class SemaphoreOwn {
    private:
        int cnr;
        std::mutex mtx;
        std::condition_variable wcv;
    public:
        SemaphoreOwn() : cnr{0}{};
        SemaphoreOwn(int size) : cnr{size}{};
        void acquire();
        void release();
        int available_permits();
}; 