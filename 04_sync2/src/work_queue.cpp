/*
    author: Haller Tobias
    date:   16.11.2022
    desc:   04_syn2
*/

#include "work_queue.h"

using namespace std;

WorkQueue::WorkQueue() {};

void WorkQueue::push(WorkPacket wp) {
  unique_lock<mutex> lck{mtx};
  q.push(wp);
}

WorkPacket WorkQueue::pop() {
  unique_lock<mutex> lck{mtx};
  WorkPacket wp = q.front();
  q.pop();
  return wp;
}

