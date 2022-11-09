#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

class Account {
    private:
        int balance{0};
    public:    
        int get_balance(); 
        void desposit(int amount); 
        bool withdraw(int amount);
};

class Depositer {
    private:
        Account& account;
        int count;
    public:
        Depositer(Account& acc, int depositCount):
            account(acc), 
            count(depositCount)
            {};
        void operator()(){
            for(int i = 0; i < count; i++){
                account.desposit(1);
            }
        }
};

#endif
