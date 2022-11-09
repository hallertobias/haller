/*
    author: Haller Tobias
    date:   09.11.2022
    desc:   03_syn1
*/

#include "CLI11.hpp"
#include "account.cpp"
#include "account.h"
#include <thread>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    /* acc.desposit(15);  /// Punkt 1
    cout << acc.withdraw(6) << endl;
    cout << acc.withdraw(10) << endl; */
    /* acc.desposit(1);
    thread t1([&](){
        cout << acc.withdraw(1) << endl;
    }); 
    thread t2([&](){
        cout << acc.withdraw(1) << endl;
    });  */

    CLI::App app("Account app");
    int balance{0};
    app.add_option("balance", balance, "Initial balance")->required();
    int deposits{5};
    app.add_option("-d,--deposits", deposits, "Count of deposits")->capture_default_str();
    CLI11_PARSE(app, argc, argv)

    Account acc{balance};
    Depositer d1{acc, deposits};
    Depositer d2{acc, deposits};
    thread t1{ref(d1)};
    thread t2{ref(d2)};
    t1.join();
    t2.join();
    cout << acc.get_balance() << endl; 
    return 0;
}