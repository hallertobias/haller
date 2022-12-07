/*
    author: Haller Tobias
    class: 5AHIF
*/

#include "semaphore.h"

#include <mutex>

using namespace std;

void Semaphore::release(){
    cnr += 1;
    wcv.notify_one();
}

void Semaphore::acquire(){
    unique_lock<mutex> ul{mtx};
    wcv.wait(ul, [&]() {
        return (cnr - 1) >= 0;
    });

    cnr -= 1;
}

int Semaphore::available_permits(){
    return cnr;
}