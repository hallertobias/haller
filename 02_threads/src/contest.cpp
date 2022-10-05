#include <iostream>
#include <thread>

using namespace std;

void c63_amg() {
    int i{};
    while(true) {
        cout << i << ". Runde C63 AMG" << endl;
        i++;
        this_thread::sleep_for(1s);
    }
}

int main() {
    c63_amg();
    return 0;
}


