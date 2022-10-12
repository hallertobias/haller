#include <iostream>
#include <thread>
#include "car.cpp"
#include <string>

using namespace std;

void help() {
    cout << "Usage: contest [-h | --help | LAPS]" << endl;
}

void error(string msg="") {
    if (msg != "") {
        cerr << msg << endl;
    } else {
        cerr << "Run with --help for more information." << endl;
    }
}

int main(int argc, char* argv[]) {
    int laps{};
    if (argc > 1) {
        if (string(argv[1]) == "-h" || string(argv[1]) == "--help") {
            help();
            return 0;
        } else {
            string s{argv[1]};
            try {
                size_t index = 0;
                laps = stoi(s, &index);
                if (index != s.length()) {
                    error("Could not convert: " + s);
                    error();
                    return 1;

                } else if (!(laps < 16 && laps >= 1)) {
                    error("Out of range (1 <= LAP'S < 16): " + s);
                    error();
                    return 1;
                }
            } catch(...) {
                error("Could not convert: " + s);
                error();
                return 1;
            }
        }
    } else {
        laps = 10;
    }
    Car c{"BWM X5 M", laps};
    Car c2{"AMG C63", laps};
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


