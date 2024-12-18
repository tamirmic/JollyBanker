#ifndef FUND_H_
#define FUND_H_

#include "transaction.h"
#include <string>
#include <vector>
#include <iostream>

class Fund{
    public:
        Fund();

        bool Deposit(int amount);
        bool Withdraw(int amount);

        void set_name(string name);
        int balance() const;
        string name() const;

    private:
        string name_;
        int balance_ = 0;
};
#endif