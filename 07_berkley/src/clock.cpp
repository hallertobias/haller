#include "clock.h"
#include <string>
#include <iostream>
#include <thread>
#include "timeutils.h"

using namespace std;

Clock::Clock(string name) {
    this->name = name;
    this->curr_time = chrono::system_clock::now();
}

Clock::Clock(string name_, int hours_, int minutes_, int seconds_) {
    this->name = name_;
    this->curr_time = set_time(this->curr_time, hours_, minutes_, seconds_);
}

void Clock::operator()() {
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));
        this->curr_time += chrono::duration<int, milli>(1000);
        cout << name << ": " << this->curr_time << endl;
    }
}