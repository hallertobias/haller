/*
    author: Haller Tobias
    date:   16.11.2022
    desc:   04_syn2
*/

#include "work_queue.h"

using namespace std;

void WorkQueue::push(WorkPacket wp) {
    unique_lock<mutex> lck{mtx};
    not_full.wait(lck, [this]{return q.size() < size;});
    q.push(wp);
    not_empty.notify_one();
}

WorkPacket WorkQueue::pop() {
    unique_lock<mutex> lck{mtx};
    not_empty.wait(lck, [this]{return q.size();});
    WorkPacket wp = q.front();
    q.pop();
    not_full.notify_one();
    return wp;
}

