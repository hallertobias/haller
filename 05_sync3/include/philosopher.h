/*
    author: Haller Tobias
    class: 5AHIF
*/

#include <thread>
#include <mutex>
#include "semaphore.h"

using namespace std;

class Philosopher {
    private: 
        int id; 
        mutex& leftFork; 
        mutex& rightFork;
    public:
        Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork) : 
          id(id),
          leftFork(leftFork),
          rightFork(rightFork)
          {};
        void operator()(Semaphore* s);
};