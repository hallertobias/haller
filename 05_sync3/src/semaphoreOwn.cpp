/*
    author: Haller Tobias
    class: 5AHIF
*/


#include <mutex>
#include "semaphoreOwn.h"

using namespace std;

void SemaphoreOwn::release(){
    cnr += 1;
    wcv.notify_one();
}

void SemaphoreOwn::acquire(){
    unique_lock<mutex> ul{mtx};
    wcv.wait(ul, [&]() {
        return (cnr - 1) >= 0;
    });
    cnr -= 1;
}

int SemaphoreOwn::available_permits(){
   return cnr;
}