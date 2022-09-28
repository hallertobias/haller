#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char *argv[]) {
    while(true){
        cout << argv[argc - 1] << endl;
        chrono::milliseconds sleeptime(500);
        this_thread::sleep_for(sleeptime);
    }
}