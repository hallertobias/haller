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
        void operator()() {}
};

int main() {
    thread t(TimeSlave{"Sklave", 12, 12, 12});
    t.join();
} 