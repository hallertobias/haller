/*
    author: Haller Tobias
    class: 5AHIF
*/

#include <iostream>
#include "philosopher.h"
#include <mutex>

using namespace std;

mutex mtx;

void println(const initializer_list<string>& v){
    lock_guard<mutex> lck(mtx);
    for(string s : v){
        cout << s << " ";
    }
    cout << endl;
}

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
