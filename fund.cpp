#include "fund.h"

Fund::Fund(){
    balance_ = 0;
}

bool Fund::Deposit(int amount){
    if(amount >= 0){
        balance_ += amount;
        return true;
    }
    cerr << "ERROR: Cannot deposit negative number." << endl;
    return false;
}

bool Fund::Withdraw(int amount){
    if(amount >= 0 && balance_ >= amount){
        balance_ -= amount;
        return true;
    }
    return false;
}

void Fund::set_name(string name){
    name_ = name;
}

int Fund::balance() const{
    return balance_;
}

string Fund::name() const{
    return name_;
}