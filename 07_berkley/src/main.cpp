#include "clock.cpp"
#include <string>

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