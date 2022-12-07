#include <mutex>
#include <thread>
#include "philosopher.cpp"
#include "semaphoreOwn.cpp"
#include "CLI11.hpp"

using namespace std;

int main(int argc, char* const argv[]) {
    CLI::App app("Dining phillosophers simulation");

    bool nodeadlock;
    app.add_option("-n, --nodeadlock", nodeadlock, "Prevent a deadlock at all");

    bool livelock;
    app.add_option("-l, --livelock", livelock, "Simulate a livelock");
    CLI11_PARSE(app, argc, argv);

    SemaphoreOwn* s;

    if (nodeadlock){
        s = new SemaphoreOwn{};
    } else {
        s = nullptr;
    }    

    timed_mutex tm1;
    timed_mutex tm2;
    timed_mutex tm3;
    timed_mutex tm4;
    timed_mutex tm5;

    Philosopher p1(1, ref(tm1), ref(tm5));
    Philosopher p2(2, ref(tm2), ref(tm1));
    Philosopher p3(3, ref(tm3), ref(tm2));
    Philosopher p4(4, ref(tm4), ref(tm3));
    Philosopher p5(5, ref(tm5), ref(tm4));

    thread t1{p1, s, livelock};
    thread t2{p2, s, livelock};
    thread t3{p3, s, livelock};
    thread t4{p4, s, livelock};
    thread t5{p5, s, livelock};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}