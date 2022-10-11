#include <iostream>
#include <thread>
#include "car.cpp"

using namespace std;

int main() {
    Car c{"BWM X5 M"};
    thread t{c};
    t.join();
    return 0;
}


