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

#endif
