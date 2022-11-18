#pragma once

#include "work_packet.h"
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

class WorkQueue {
    private:
       queue<WorkPacket> q;
       mutex mtx;
       condition_variable not_empty;
       condition_variable not_full;
       size_t size;
    public:
        WorkQueue(size_t size){
            this->size = size;  
        };        
        void push(WorkPacket wq);
        WorkPacket pop();
};