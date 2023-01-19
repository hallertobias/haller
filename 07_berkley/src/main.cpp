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
        void set_latency(long latency) {
            this->p1.set_latency(latency);
            this->p2.set_latency(latency);
        }
};

class TimeSlave {
    private:
        string name;
        Clock clock;
        Channel* channel = new Channel();
    public:
        TimeSlave(string name, int hours, int minutes, int seconds) : clock(name + " Clock", hours, minutes, seconds) {
            this->name = name;
        };
        void operator()() {
            long syncTime;
            while(this->channel->getPipe1() >> syncTime) {
                if (syncTime > 0) {
                    this->clock.from_time(syncTime);
                } else {
                    cout << this->name + "Slave request time: " + to_string(this->clock.to_time()) << endl;
                    this->channel->getPipe2() << this->clock.to_time(); 
                }
            }
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
            while(true) {
                doBerkley();
                this_thread::sleep_for(10s); 
            }
        };
        void setChannel1(Channel* channel) {
            this->channel1 = channel;
        };
        void setChannel2(Channel* channel) {
            this->channel2 = channel;
        };
        void doBerkley() {
            long slave1Time;
            long slave2Time;
            long time; 

            cout << "Starting berkley algo with: " + to_string(this->clock.to_time()) << endl;

            this->channel1->getPipe1() << -1;
            this->channel2->getPipe2() << -1;

            time = this->clock.to_time();

            this->channel1->getPipe2() >> slave1Time;
            this->channel2->getPipe2() >> slave2Time;

            long syncTime = (time + slave1Time + slave2Time) / 3;

            this->clock.from_time(syncTime);
            this->channel1->getPipe1() << syncTime;
            this->channel2->getPipe2() << syncTime;

        }
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