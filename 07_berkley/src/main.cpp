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
            long value;
            Pipe<long>& pipe = this->channel->getPipe1();
            while (pipe >> value) {
                std::cout << name << ": " << value << std::endl;
            }
            std::cout << name << ": end" << std::endl;
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
            for (int i = 0; i < 3; i++) {
            this->channel1->getPipe1() << i;
            this->channel2->getPipe2() << i;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            this->channel1->getPipe1().close();
            this->channel2->getPipe2().close();
            std::cout << "master: end" << std::endl;
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