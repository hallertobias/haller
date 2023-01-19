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
        this_thread::sleep_for(1s + chrono::milliseconds(this->clockSpeed + this->clockSlowndon));
        this->curr_time += 1s;
        cout << name << ": " << this->curr_time << endl;
    }
}

void Clock::set_time(int hours, int minutes, int seconds)
{
    chrono::time_point<chrono::system_clock> time = timeutils::set_time(this->curr_time, hours, minutes, seconds);
    if (time < this->curr_time) {
        this->clockSlowndon = 100;
    } else {
        this->curr_time = timeutils::set_time(this->curr_time, hours, minutes, seconds);
    }
}

tuple<int, int, int> Clock::get_time()
{
    return timeutils::get_time(this->curr_time);
}

long Clock::to_time()
{
    return chrono::system_clock::to_time_t(this->curr_time);
}

void Clock::from_time(long time)
{
    cout << this->name + " time update: " + to_string(time) << endl;
    this->curr_time = chrono::system_clock::from_time_t(time);
}

void Clock::set_time_monoton(bool monton) {
    this->monoton = monton;
}

void Clock::setClockSpeed(int clockSpeed) {
    this->clockSpeed = clockSpeed;
}