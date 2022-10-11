#include <iostream>
#include "car.h"
#include <string>
#include <random>

using namespace std;

Car::Car(string name) {
    carName = name;
}

void Car::printOut() {
    int i{1};
    string output;
    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{1, 10};
    while(i <= 10) {
        int time = dis(gen);
        double rounded = ceil(dis(gen)*100.00)/100.00;
        output = to_string(i) + ". Runde " + this->carName
         + " (" + to_string(rounded).substr(0, 4) + "s)" + "\n";
        cout << output << flush;
        i++;
        this_thread::sleep_for(chrono::milliseconds{time}*1000);
    }
}

void Car::operator()() {
    printOut();
}