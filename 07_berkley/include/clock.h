#pragma once

#include <string>
#include <chrono>

using namespace std;

class Clock {
public:
    Clock(string name);
    Clock(string name_, int hours_, int minutes_, int seconds_);
    void operator()();
private:
    string name;
    chrono::time_point<std::chrono::system_clock> curr_time;
};