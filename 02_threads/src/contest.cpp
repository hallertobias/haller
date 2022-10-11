#include <iostream>
#include <thread>
#include "car.cpp"

using namespace std;

int main() {
    Car c{"BWM X5 M"};
    thread t{c};
    Car c2{"AUDI RS6"};
    thread t2{c2};
    Car c3{"AMG C63"};
    thread t3{c3};
    t.join();
    t2.join();
    t3.join();
    return 0;
}


