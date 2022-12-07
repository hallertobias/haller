/*
    author: Haller Tobias
    class: 5AHIF
*/

#include <iostream>
#include "philosopher.h"

using namespace std;

void Philosopher::operator()() {
    while(true){

        cout << "Philosopher " << id << " is thinking..." << endl;
        this_thread::sleep_for(1s);

        cout << "Philosopher " << id << " attempts to get left fork" << endl;

        leftFork.lock();

        cout << "Philosopher " << id << " got left fork. Now he wants the right one... " << endl;

        cout << "Philosopher " << id << " attempts to get right fork" << endl;

        rightFork.lock();

        cout << "Philosopher " << id << " got right fork. Now he is eating..." << endl;

        this_thread::sleep_for(2s);

        cout << "Philosopher " << id << " finished eating" << endl;
        cout << "Philosopher " << id << " released left fork" << endl;
        leftFork.unlock();
        cout << "Philosopher " << id << " released right fork" << endl;
        rightFork.unlock();
    }
};
