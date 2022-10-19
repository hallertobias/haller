#include "account.h"
#include <thread>

using namespace std;

int Account::get_balance() {
    return this->balance;
}

void Account::desposit(int amount) {
    this->balance += amount;
}

bool Account::withdraw(int amount) {
    if ((this->balance - amount) >= 0) {
        this_thread::yield();
        this->balance -= amount;
        return true;
    } else {
        return false;
    }
}