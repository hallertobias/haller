#include <iostream>
#include "car.h"
#include <string>

using namespace std;

Car::Car(string name) {
    carName = name;
}

void Car::printOut() {
    int i{};
    while(true) {
        cout << i << ". Runde " << this->carName << endl;
        i++;
        this_thread::sleep_for(1s);
    }
}

void Car::operator()() {
    printOut();
}