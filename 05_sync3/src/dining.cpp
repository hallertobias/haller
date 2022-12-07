#include <mutex>
#include <thread>
#include "philosopher.cpp"

using namespace std;

int main() {
    mutex mutexRight;
    mutex mutexLeft;

    Philosopher p1(1, mutexRight, mutexLeft);
    Philosopher p2(2, mutexRight, mutexLeft);
    Philosopher p3(3, mutexRight, mutexLeft);

    thread t1{p1};
    thread t2{p2};
    thread t3{p3};

    t1.join();
    t2.join();
    t3.join();
}