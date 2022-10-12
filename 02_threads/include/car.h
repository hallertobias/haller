#ifndef _CAR_H_
#define _CAR_H_

#include <string>

using namespace std;

class Car {
    private:
        double timeSum;
        string carName;
        int laps;
    public:    
        Car(string carName, int laps);
        void printOut();
        void operator()();
        string getCarName();
        double getTimeSum();
};

#endif
