#include <iostream>
#include <unistd.h> // fork
#include <chrono>
#include <thread>
#include <csignal>

using namespace std;

int main() {
    auto pid{fork()};
    int counter = 0;
    char c{};
    chrono::milliseconds sleeptime(500);
    if (pid == 0) {
        c = 'A';
        }
    if (pid != 0) {
        c = 'B';
    }
    while (true) {
        if (pid != 0 && counter == 6) {
            cout << endl;
            kill(pid, SIGKILL);
            exit(EXIT_SUCCESS);
        }
        cout << c << flush;
        this_thread::sleep_for(sleeptime);
        counter++;
    }
}
