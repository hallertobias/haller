#pragma once

#include "clock.h"
#include <string>

using namespace std;

class Timeslave {
    private: 
        Clock clock;
        string name;
    public:
        Timeslave(string name_, int hours_, int minutes_, int seconds_);
        void operator()();
};