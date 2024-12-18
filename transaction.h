#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <iostream>
#include <string>
using namespace std;

class Transaction{
    public:
        Transaction();

        //D: Deposit assets into a fund
        //W: Withdraw assets from a fund
        Transaction(char type, int account_id, int fund_type, int amount, bool success = true);

        //T: Transfer assets between funds
        Transaction(char type, int account_id, int fund_type, int transfer_account_id, int transfer_fund_type, int amount, bool swap_ids = false, bool success = true);

        //A: Display the history of all transactions for a client account
        Transaction(char type, int account_id);

        //F: Display the history for all transactions of a given fund
        Transaction(char type, int account_id, int fund_type);

        //O: Open a client account and instantiate eight funds with 0 assets each
        Transaction(char type, int account_id, string first_name, string last_name);

        char type() const;
        string first_name() const;
        string last_name() const;
        int account_id() const;
        int fund_type() const;
        void set_fund_type(int fund_type);
        int transfer_account_id() const;
        int transfer_fund_type() const;
        void set_transfer_fund_type(int transfer_fund_type);
        int amount() const;
        bool swap_ids() const;
        bool success() const;
        void set_success(bool success);
        
        friend ostream& operator<<(ostream &out, const Transaction& t);

    private:
        char type_;
        string first_name_;
        string last_name_;
        int account_id_;
        int fund_type_;
        int transfer_account_id_;
        int transfer_fund_type_;
        int amount_;
        bool swap_ids_;
        bool success_;
};
#endif