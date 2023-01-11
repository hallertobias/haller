#pragma once

#include <string>
#include <chrono>

using namespace std;

class Clock {
public:
    Clock(std::string name);
    void operator()();
private:
    string name;
    chrono::time_point<std::chrono::system_clock> curr_time;
};