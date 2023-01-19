#pragma once

#include <string>
#include <chrono>
#include <tuple>

using namespace std;

class Clock {
    private:
        string name;
        chrono::time_point<chrono::system_clock> curr_time;
    public:
        Clock(string name);
        Clock(string name, int hours, int minutes, int seconds);
        void operator()();
        void set_time(int, int, int);
        tuple<int, int, int> get_time();
        long to_time();
        void from_time(long time);
};