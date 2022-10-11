#ifndef _CAR_H_
#define _CAR_H_

#include <string>

using namespace std;

class Car {
    public:    
        Car(string carName);
        string carName;
        void printOut();
        void operator()();
};

#endif
