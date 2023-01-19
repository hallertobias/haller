#include "clock.cpp"
#include <string>
#include "pipe.h"

class Channel {
    private: 
        Pipe<long> p1;
        Pipe<long> p2;
    public:
        Pipe<long>& getPipe1() {
            return p1;
        };
        Pipe<long>& getPipe2() {
            return p2;
        };
};

class TimeSlave {
    private:
        string name;
        Clock clock;
        Channel* channel{new Channel()};
    public:
        TimeSlave(string name, int hours, int minutes, int seconds) : clock(name + " Clock", hours, minutes, seconds) {
            this->name = name;
        };
        void operator()() {
            clock();
        };
        Channel* getChannel() {
            return channel;
        };
};

class TimeMaster {
    private: 
        string name;
        Clock clock;
        Channel* channel1{new Channel()};
        Channel* channel2{new Channel()};
    public:
        TimeMaster(string name, int hours, int minutes, int seconds) : clock(name + " Clock", hours, minutes, seconds) {
            this->name = name;
        }
        void operator()() {
            clock();
        };
        void setChannel1(Channel* channel) {
            this->channel1 = channel;
        };
        void setChannel2(Channel* channel) {
            this->channel2 = channel;
        };
};

int main() {
    TimeMaster master{"Test Meister", 12, 12, 12};
    thread masterThread{ref(master)};
    TimeSlave slave1{"Test Sklave 1", 11, 12, 12};
    thread slave1Thread{ref(slave1)};
    TimeSlave slave2{"Test Sklave 2", 10, 12, 12};
    thread slave2Thread{ref(slave2)};

    master.setChannel1(slave1.getChannel());
    master.setChannel2(slave2.getChannel());

    slave1Thread.join();
    slave2Thread.join();
    masterThread.join(); 
} 