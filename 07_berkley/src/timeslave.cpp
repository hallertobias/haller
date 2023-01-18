#include "timeslave.h"
#include "clock.cpp"
#include <string>

Timeslave::Timeslave(string name_, int hours_, int minutes_, int seconds_) {
    this->name = name_;
    this->clock = Clock(name_, hours_, minutes_, seconds_);
}

void Timeslave::operator()() {

}