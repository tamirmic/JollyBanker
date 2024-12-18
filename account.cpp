#include "account.h"

Account::Account(int id, string first_name, string last_name){
    id_ = id;
    first_name_ = first_name;
    last_name_ = last_name;

    for(int i = 0; i < kNumberOfFunds; i++){
        funds_[i].set_name(kFundNames[i]);
    }
}

int Account::id() const{
    return id_;
}

string Account::first_name() const{
    return first_name_;
}

string Account::last_name() const{
    return last_name_;
}

bool Account::IsFundIndexValid(int fund_type) const {
    if (fund_type > kNumberOfFunds - 1 || fund_type < 0) {
        cerr << "ERROR: Fund number " << fund_type << " is invalid." << endl;
        return false;
    }
    return true;
}

bool Account::Transfer(Transaction& transaction, Account &target_account) {
    if(!IsFundIndexValid(transaction.fund_type()) || !IsFundIndexValid(transaction.transfer_fund_type())){
        return false;
    }

    if(!IsTransferValid(transaction)){
        transaction.set_success(false);
        AddTransaction(transaction);
        return false;
    }
    
    if(!Withdraw(transaction, false)){
        transaction.set_success(false);
        AddTransaction(transaction);
        return false;
    }

    //Make the deposit of the transfer in the target account (can't fail as already check we have funds)
    target_account.funds_[transaction.transfer_fund_type()].Deposit(transaction.amount());

    //Add transfer transaction to source account fund
    AddTransaction(transaction);
    //Add transfer transaction to target account fund
    target_account.AddTransaction(Transaction(
        transaction.type(),
        transaction.account_id(), 
        transaction.transfer_fund_type(), 
        transaction.transfer_account_id(), 
        transaction.fund_type(), 
        transaction.amount(), true, true));
    return true;
}

bool Account::IsTransferValid(Transaction& transaction){
    //Transaction(char type, int account_id, int fund_type, int transfer_account_id, int transfer_fund_type, int amount, bool swap_ids = false, bool success = true);
    //Check if transfer in the same account
    if(transaction.account_id() == transaction.transfer_account_id()){
        int fund_type = transaction.fund_type();
        int transfer_fund_type = transaction.transfer_fund_type();
        //Invalid transfer - same account same fund
        if(fund_type == transfer_fund_type){
            cerr << "ERROR: Cannot transfer to the same account and same fund." << endl;
            return false;
        }

        //Invalid transfer - same account, transfer to joint funds but insufficient funds in source fund
        if(fund_type == 0 && transfer_fund_type == 1){
            if(funds_[0].balance() < transaction.amount()){
                return false;
            }
        }
        if(fund_type == 1 && transfer_fund_type == 0){
            if(funds_[1].balance() < transaction.amount()){
                return false;
            }
        }
        if(fund_type == 2 && transfer_fund_type == 3){
            if(funds_[2].balance() < transaction.amount()){
                return false;
            }
        }
        if(fund_type == 3 && transfer_fund_type == 2){
            if(funds_[3].balance() < transaction.amount()){
                return false;
            }
        }
    }
    return true;
}

bool Account::Deposit(Transaction& transaction){
    if(!IsFundIndexValid(transaction.fund_type())){
        return false;
    }
    bool deposit_results = funds_[transaction.fund_type()].Deposit(transaction.amount());
    transaction.set_success(deposit_results);
    AddTransaction(transaction);
    return true;
}

bool Account::Withdraw(Transaction& transaction, bool add_transaction) {
    int fund_type = transaction.fund_type();
    int amount = transaction.amount();

    if(!IsFundIndexValid(transaction.fund_type())){
        return false;
    }
    if(WithdrawFromFund(fund_type, amount)){
        if(add_transaction){
            AddTransaction(transaction);
        }
        return true;
    }

    if(WithdrawFromJointFunds(fund_type, amount, add_transaction)){
        return true;
    }
    if(add_transaction){
        //Not enough funds to perform the transfer
        transaction.set_success(false);
        AddTransaction(transaction);
    }
    return false;
}

bool Account::WithdrawFromFund(int fund_type, int amount){
    if(funds_[fund_type].Withdraw(amount)){
        return true;
    }
    if(amount < 0){
        cerr << "ERROR: Cannot withdraw a negative number." << endl;
    }
    return false;
}

bool Account::WithdrawFromJointFunds(int fund_type, int amount, bool add_transaction){
    if(fund_type == 0 && (amount <= funds_[0].balance() + funds_[1].balance())){
        WithdrawJointFunds(0, 1, amount, add_transaction);
        return true;
    }
    if(fund_type == 1 && (amount <= funds_[1].balance() + funds_[0].balance())){
        WithdrawJointFunds(1, 0, amount, add_transaction);
        return true;
    }
    if(fund_type == 2 && (amount <= funds_[2].balance() + funds_[3].balance())){
        WithdrawJointFunds(2, 3, amount, add_transaction);
        return true;
    }
    if(fund_type == 3 && (amount <= funds_[3].balance() + funds_[2].balance())){
        WithdrawJointFunds(3, 2, amount, add_transaction);
        return true;
    }
    return false;
}


void Account::WithdrawJointFunds(int fund_type1, int fund_type2, int amount, bool add_transaction) {
    int balance_remove = funds_[fund_type1].balance();
    funds_[fund_type1].Withdraw(balance_remove);
    int remaining_amount = amount - balance_remove;
    funds_[fund_type2].Withdraw(remaining_amount);
    if(add_transaction){
        AddTransaction(Transaction('W', id_, fund_type1, balance_remove));
        AddTransaction(Transaction('W', id_, fund_type2, remaining_amount));
    }
}

void Account::AddTransaction(const Transaction& transaction){
    account_history_.push_back(transaction);
}

void Account::DisplayFundHistory(int fund_type) const {
    if(IsFundIndexValid(fund_type)){
        const Fund& fund = funds_[fund_type];
        cout << "Transaction History for " << first_name() << " " << last_name() << " " << fund.name() << ": $" << fund.balance() << endl;

        if (FundHasTransactions(fund_type)) {
            PrintFundTransactions(fund_type);
        }
        else {
            cout << "(No transactions)" << endl;
        }
        cout << endl;
    }
}

void Account::DisplayAccountHistory() const{
    cout << "Transaction History for " << first_name() << " " << last_name() << " by fund." << endl;

    for(int fund_type = 0; fund_type < kNumberOfFunds; fund_type++){
        if(FundHasTransactions(fund_type)){
            cout << kFundNames[fund_type] << ": $" << funds_[fund_type].balance() << endl;
            PrintFundTransactions(fund_type);
        }
    }
    cout << endl;
}

bool Account::FundHasTransactions(int fund_type) const
{
    for (int i = 0; i < account_history_.size(); i++) {
        Transaction transaction = account_history_[i];
        if (transaction.fund_type() == fund_type) {
            return true;
        }
    }
    return false;
}

void Account::PrintFundTransactions(int fund_type) const
{
    for (int i = 0; i < account_history_.size(); i++) {
        Transaction transaction = account_history_[i];
        if (transaction.fund_type() == fund_type) {
            if (transaction.type() == 'T' && transaction.swap_ids()) {
                transaction.set_fund_type(transaction.transfer_fund_type());
                transaction.set_transfer_fund_type(fund_type);
            }
            cout << transaction << endl;
        }
    }
}

ostream& operator<<(ostream &out, const Account& p_account){
    out << p_account.first_name() << " " << p_account.last_name() << " Account ID: " << p_account.id() << endl;

    for(int i = 0; i < kNumberOfFunds; i++){
        out << "   " << kFundNames[i] << ": $" << p_account.funds_[i].balance() << endl;
    }
    out << endl;
    return out;
}