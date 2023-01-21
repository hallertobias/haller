#include "clock.cpp"
#include <string>
#include "pipe.h"
#include "CLI11.hpp"

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
                    long slaveTime = clock.to_time();
                    if (clock.getMonoton() && syncTime < slaveTime) {
                        cout << this->name << " slowing down clock" << endl;
                        this->clock.set_time_monoton(true);
                    } else {
                        this->clock.set_time_monoton(false);
                        this->clock.from_time(syncTime);

                        if (this->clock.getMonoton()) {
                            cout << this->name << " time corrected" << endl;
                        } else {
                            cout << this->name << " setting time to " << syncTime << endl;
                        }
                    }
                } else {
                    cout << this->name + " request time: " + to_string(this->clock.to_time()) << endl;
                    this->channel->getPipe2() << this->clock.to_time(); 
                }
            }
        };
        Channel* getChannel() {
            return channel;
        };
        void set_time_monoton(bool monoton) {
            this->clock.set_time_monoton(monoton);
        };
        void setClockSpeed(int clockSpeed) {
            this->clock.setClockSpeed(clockSpeed);
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
            this->channel2->getPipe1() << -1;

            time = this->clock.to_time();

            this->channel1->getPipe2() >> slave1Time;
            this->channel2->getPipe2() >> slave2Time;

            long syncTime = (time + slave1Time + slave2Time) / 3;

            this->clock.from_time(syncTime);
            this->channel1->getPipe1() << syncTime;
            this->channel2->getPipe1() << syncTime;
        }
        void set_time_monoton(bool monoton) {
            this->clock.set_time_monoton(monoton);
        };
        void setClockSpeed(int clockSpeed) {
            this->clock.setClockSpeed(clockSpeed);
        };
};

int main(int argc, char* argv[]) {
    bool monoton = false;
    int latency1 = 0;
    int latency2 = 0;
    int deviSlave1 = 1000;
    int deviSlave2 = 1000;
    int deviMaster = 1000;

    CLI::App app("Berkley Algo"); 

    app.add_flag("--monotone", monoton, "set monotone mode");
    app.add_option("--latency1", latency1, "latency to channel 1 (both directions)");
    app.add_option("--latency2", latency2, "latency to channel 2 (both directions)");
    app.add_option("--deviation1", deviSlave1, "deviation of clock of slave 1");
    app.add_option("--deviation2", deviSlave2, "deviation of clock of slave 2");
    app.add_option("--deviationm", deviMaster, "deviation of clock of master");

    CLI11_PARSE(app, argc, argv); 

    TimeMaster master{"Test Meister", 0, 0, 11};
    TimeSlave slave1{"Test Sklave 1", 0, 0, 33};
    TimeSlave slave2{"Test Sklave 2", 0, 0, 40};

    master.set_time_monoton(monoton);
    slave1.set_time_monoton(monoton);
    slave2.set_time_monoton(monoton);

    slave1.getChannel()->set_latency(latency1);
    slave2.getChannel()->set_latency(latency2);

    slave1.setClockSpeed(deviSlave1);
    slave2.setClockSpeed(deviSlave2);
    master.setClockSpeed(deviMaster);

    master.setChannel1(slave1.getChannel());
    master.setChannel2(slave2.getChannel());

    thread masterThread{ref(master)};
    thread slave1Thread{ref(slave1)};
    thread slave2Thread{ref(slave2)};

    slave1Thread.join();
    slave2Thread.join();
    masterThread.join(); 
} 