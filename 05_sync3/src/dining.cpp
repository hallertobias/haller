#include <mutex>
#include <thread>
#include "philosopher.cpp"
#include "semaphoreOwn.cpp"

using namespace std;

int main() {
    mutex mutexRight;
    mutex mutexLeft;

    SemaphoreOwn* s = new SemaphoreOwn{5};

    Philosopher p1(1, mutexRight, mutexLeft);
    Philosopher p2(2, mutexRight, mutexLeft);
    Philosopher p3(3, mutexRight, mutexLeft);
    Philosopher p4(4, mutexRight, mutexLeft);
    Philosopher p5(5, mutexRight, mutexLeft);

    thread t1{p1, s};
    thread t2{p2, s};
    thread t3{p3, s};
    thread t4{p4, s};
    thread t5{p5, s};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}