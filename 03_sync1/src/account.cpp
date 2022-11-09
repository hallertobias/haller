#include "account.h"
#include <thread>
#include <mutex>

using namespace std;

mutex m;

int Account::get_balance() {
    return this->balance;
}

void Account::desposit(int amount) {
    unique_lock<mutex> ul{m};
    this->balance += amount;
}

bool Account::withdraw(int amount) {
    lock_guard<mutex> guard{m};
    if ((this->balance - amount) >= 0) {
        this_thread::yield();
        this->balance -= amount;
        return true;
    } else {
        return false;
    }
}