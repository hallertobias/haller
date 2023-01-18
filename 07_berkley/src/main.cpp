#include "clock.cpp"
#include <string>
#include "pipe.h"

class TimeSlave {
    private:
        string name;
        Clock clock;
    public:
        TimeSlave(string name, int hours, int minutes, int seconds) : clock(name + " Clock", hours, minutes, seconds) {
            this->name = name;
        };
        void operator()() {
            clock();
        }
};

class Channel {
    private: 
        Pipe<long> p1;
        Pipe<long> p2;
    public:
        Pipe<long>& getPipe1() {
            return p1;
        }
        Pipe<long>& getPipe2() {
            return p2;
        }
}

class TimeMaster {
    private: 
        string name;
        Clock clock;
    public:
        TimeMaster(string name, int hours, int minutes, int seconds) : clock(name + " Clock", hours, minutes, seconds) {
            this->name = name;
        }
        void operator()() {
            clock();
        };
};

int main() {
    thread t(TimeSlave{"Sklave 1", 12, 12, 12});
    t.join();
    thread t2(TimeSlave{"Sklave 2", 12, 12, 12});
    t2.join();
} 