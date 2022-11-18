/*
    author: Haller Tobias
    date:   16.11.2022
    desc:   04_syn2
*/

#include "CLI11.hpp"
#include <thread>
#include <iostream>
#include "work_packet.h"
#include "work_queue.cpp"
#include <chrono>
#include <random>

using namespace std;

void worker (int id, WorkQueue& q){
    string output;
    double wait_worker;
    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{1, 10};
    while(true){   
        output =  "W" + to_string(id) + ": Want work packet \n";
        cout << output << flush;
        WorkPacket WP{q.pop()};
        wait_worker = dis(gen);
        chrono::milliseconds time_to_wait_worker{int (wait_worker * 1000)};
        output =  "W" + to_string(id) + ": Got work packet " + to_string(WP.getID()) + "\n";
        cout << output << flush;
        this_thread::sleep_for(time_to_wait_worker);
        output = "W" + to_string(id) + ": Processed work packet " + to_string(WP.getID()) + " (" + to_string(wait_worker) + ")" + "\n";
        cout << output << flush;
    }
}



int main(int argc, char* const argv[]) {
    CLI::App app("Boss and worker simulation");
    size_t size;
    app.add_option("size", size, "Size of the queue")->required();
    CLI11_PARSE(app, argc, argv);

    int i{0};
    WorkQueue q(size);
    string boss_output;

    thread t1{worker, 1, ref(q)};
    thread t2{worker, 2, ref(q)};
    thread t3{worker, 3, ref(q)};

    double wait_boss;
    random_device rd;
    mt19937 gen{rd()};
    uniform_real_distribution<> dis{0, 1};

    while(true){
        WorkPacket WP{WorkPacket(i)};
        q.push(WP);
        wait_boss = dis(gen);
        chrono::milliseconds time_to_wait_boss{int (wait_boss * 1000)};
        boss_output = "B: Submitted work packet " + to_string(i) + "\n";
        cout << boss_output << flush;
        this_thread::sleep_for(time_to_wait_boss);
        i++;
    }

    t1.join();
    t2.join();
    t3.join();
}