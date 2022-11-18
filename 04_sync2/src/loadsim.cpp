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

using namespace std;

int main() {
    chrono::milliseconds sleeptime(500);
    int id = 0;
    WorkQueue q{};
    while(true) {
        WorkPacket wp{id};
        q.push(wp);
        cout << "B: Submitted work packet " << id << endl;
        id++;
        this_thread::sleep_for(sleeptime);
    }
    return 0;
}