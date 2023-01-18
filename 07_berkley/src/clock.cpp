#include "clock.h"
#include <string>
#include <iostream>
#include <thread>
#include "timeutils.h"

using namespace std;

Clock::Clock(string name)
{
    this->name = name;
    this->curr_time = chrono::system_clock::now();
}

Clock::Clock(string name, int hours, int minutes, int seconds)
{
    this->name = name;
    this->curr_time = chrono::system_clock::now();
    this->curr_time = timeutils::set_time(this->curr_time, hours, minutes, seconds);
}

void Clock::operator()()
{
    while (true)
    {
        this_thread::sleep_for(chrono::seconds(1));
        this->curr_time += 1s;
        cout << name << ": " << this->curr_time << endl;
    }
}

void Clock::set_time(int hours, int minutes, int seconds)
{
    this->curr_time = timeutils::set_time(this->curr_time, hours, minutes, seconds);
}

tuple<int, int, int> Clock::get_time()
{
    return timeutils::get_time(this->curr_time);
}