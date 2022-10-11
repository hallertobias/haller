#include <iostream>
#include <thread>
#include "car.cpp"

using namespace std;

int main() {
    Car c{"BWM X5 M"};
    Car c2{"AMG C63"};
    thread t{ref(c)};
    thread t2{ref(c2)};
    t.join();
    t2.join();
    if(c.getTimeSum() > c2.getTimeSum()) {
        cout << "Sieger ist: " << c2.getCarName() << " mit " << c2.getTimeSum() << "s" << endl;
        cout << "Verlierer ist: " << c.getCarName() << " mit " << c.getTimeSum() << "s" << endl;
    } else {
        cout << "Sieger ist: " << c.getCarName() << " mit " << c.getTimeSum() << "s" << endl;
        cout << "Verlierer ist: " << c2.getCarName() << " mit " << c2.getTimeSum() << "s" << endl;
    }
    return 0;
}


