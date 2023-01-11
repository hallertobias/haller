#include "clock.h"
#include <string>
#include <iostream>
#include <thread>
#include "timeutils.h"

using namespace std;

Clock::Clock(string name) {
    this->name = name;
}

void Clock::operator()() {
    this->curr_time = chrono::system_clock::now();
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(1000));
        this->curr_time += chrono::duration<int, milli>(1000);
        cout << name << ": " << this->curr_time << endl;
    }
}