#include "clock.cpp"

int main() {
    thread t{Clock{"Test"}};
    t.join();
}