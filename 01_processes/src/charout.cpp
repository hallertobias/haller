#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char *argv[]) {
    chrono::milliseconds sleeptime(500);
    while(true){
        cout << argv[argc - 1] << flush;
        this_thread::sleep_for(sleeptime);
    }
}