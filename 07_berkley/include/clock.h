#pragma once

#include <string>
#include <chrono>

using namespace std;

class Clock {
    private:
        string name;
        chrono::time_point<chrono::system_clock> curr_time = chrono::system_clock::now();
    public:
        Clock(string name);
        Clock(string name_, int hours_, int minutes_, int seconds_);
        void operator()();
};