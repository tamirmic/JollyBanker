#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include "transaction.h"
#include "fund.h"
using namespace std;

const int kNumberOfFunds = 8;

const string kFundNames[] = {
    "Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund"
};

class Account{
    public:
        Account(int id, string first_name, string last_name);

        int id() const;
        string first_name() const;
        string last_name() const;
        
        bool Transfer(Transaction& transaction, Account &target_account);
        bool Deposit(Transaction& transaction);
        bool Withdraw(Transaction& transaction, bool add_transaction);
        void DisplayFundHistory(int fund_type) const;
        void DisplayAccountHistory() const;

        friend ostream& operator<<(ostream &out, const Account& p_account);

    private:
        int id_;
        string first_name_;
        string last_name_;

        Fund funds_[kNumberOfFunds];
        vector<Transaction> account_history_;

        void AddTransaction(const Transaction& transaction);
        bool IsFundIndexValid(int fund_type) const;
        bool IsTransferValid(Transaction& transaction);
        bool WithdrawFromFund(int fund_type, int amount);
        bool WithdrawFromJointFunds(int fund_type, int amount, bool add_transaction);
        void WithdrawJointFunds(int fund_type1, int fund_type2, int amount, bool add_transaction);
        bool FundHasTransactions(int fund_type) const;
        void PrintFundTransactions(int fund_type) const;
};
#endif