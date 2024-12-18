#include "transaction.h"

Transaction::Transaction() {
}

//constructor for deposit and withdraw
Transaction::Transaction(char type, int account_id, int fund_type, int amount, bool success){
    type_ = type;
    account_id_ = account_id;
    fund_type_ = fund_type;
    transfer_account_id_ = 0;
    transfer_fund_type_ = 0;
    amount_ = amount;
    success_ = success;
}

//constructor for transfer
Transaction::Transaction(char type, int account_id, int fund_type, int transfer_account_id, int transfer_fund_type, int amount, bool swap_ids, bool success){
    type_ = type;
    account_id_ = account_id;
    fund_type_ = fund_type;
    transfer_account_id_ = transfer_account_id;
    transfer_fund_type_ = transfer_fund_type;
    amount_ = amount;
    swap_ids_ = swap_ids;
    success_ = success;
}

//constructor for account history
Transaction::Transaction(char type, int account_id){
    type_ = type;
    account_id_ = account_id;
    fund_type_ = 0;
    transfer_account_id_ = 0;
    transfer_fund_type_ = 0;
    amount_ = 0;
}

//constructor for fund history
Transaction::Transaction(char type, int account_id, int fund_type){
    type_ = type;
    account_id_ = account_id;
    fund_type_ = fund_type;
    transfer_account_id_ = 0;
    transfer_fund_type_ = 0;
    amount_ = 0;
}

//constructor for open account
Transaction::Transaction(char type, int account_id, string first_name, string last_name){
    type_ = type;
    account_id_ = account_id;
    first_name_ = first_name;
    last_name_ = last_name;
    fund_type_ = 0;
    transfer_account_id_ = 0;
    transfer_fund_type_ = 0;
    amount_ = 0;
}

char Transaction::type() const{
    return type_;
}

string Transaction::first_name() const{
    return first_name_;
}

string Transaction::last_name() const{
    return last_name_;
}

int Transaction::account_id() const{
    return account_id_;
}

int Transaction::fund_type() const{
    return fund_type_;
}

void Transaction::set_fund_type(int fund_type) {
    fund_type_ = fund_type;
}

int Transaction::transfer_account_id() const{
    return transfer_account_id_;
}

int Transaction::transfer_fund_type() const{
    return transfer_fund_type_;
}

void Transaction::set_transfer_fund_type(int transfer_fund_type) {
    transfer_fund_type_ = transfer_fund_type;
}

int Transaction::amount() const{
    return amount_;
}

bool Transaction::swap_ids() const {
    return swap_ids_;
}

bool Transaction::success() const{
    return success_;
}

void Transaction::set_success(bool success){
    success_ = success;
}

ostream& operator<<(ostream &out, const Transaction &t){
    if (t.type() == 'D' || t.type() == 'W') {
        out << "   " << t.type() << " " << t.account_id() << " " << t.fund_type() << " " << t.amount() << (t.success() ? "" : " (Failed)");
    }
    else if (t.type() == 'T') {
        out << "   T " << t.account_id() << " " << t.fund_type() << " " << t.transfer_account_id() << " " << t.transfer_fund_type() << " " << t.amount() << (t.success() ? "" : " (Failed)");
    }
    else if (t.type() == 'A') {
        out << "   A " << t.account_id();
    }
    else if (t.type() == 'F') {
        out << "   F " << t.account_id() << " " << t.fund_type();
    }
    else if (t.type() == 'O') {
        out << "   O " << t.account_id() << " " << t.first_name() << " " << t.last_name();
    }
    return out;
}