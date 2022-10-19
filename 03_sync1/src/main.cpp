#include "account.cpp"
#include <thread>
#include <iostream>

using namespace std;

int main() {
    Account acc{};
    /* acc.desposit(15);  /// Punkt 1
    cout << acc.withdraw(6) << endl;
    cout << acc.withdraw(10) << endl; */
    acc.desposit(1);
    thread t1([&](){
        cout << acc.withdraw(1) << endl;
    }); 
    thread t2([&](){
        cout << acc.withdraw(1) << endl;
    }); 
    t1.join();
    t2.join();
    return 0;
}