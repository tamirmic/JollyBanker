#include "jolly_banker.h"

JollyBanker::JollyBanker(){

}

bool JollyBanker::Init(string transactions_file){
    ifstream in_file;
    in_file.open(transactions_file);
    if(!in_file){
        return false;
    }

    string transaction_line;
    while(getline(in_file, transaction_line)){
        istringstream stream(transaction_line);
        char type;
        Transaction transaction;
        stream >> type;
        switch(type){
            case 'D': {
                transaction = InitDepositTransaction(type, stream);
                break;
            }
            case 'W': {
                transaction = InitWithdrawTransaction(type, stream);
                break;
            }
            case 'T': {
                transaction = InitTransferTransaction(type, stream);
                break;
            }
            case 'A': {
                transaction = InitAccountHistoryTransaction(type, stream);
                break;
            }
            case 'F': {
                transaction = InitFundHistoryTransaction(type, stream);
                break;
            }
            case 'O': {
                transaction = InitOpenTransaction(type, stream);
                break;
            }
        }
        transaction_list_.push(transaction);
    }

    in_file.close();
    return true;
}

Transaction JollyBanker::InitDepositTransaction(char type, istringstream &stream){
    int account_id, fund_type, amount;
    stream >> account_id >> fund_type >> amount;
    Transaction transaction(type, account_id, fund_type, amount);
    return transaction;
}

Transaction JollyBanker::InitWithdrawTransaction(char type, istringstream& stream) {
    int account_id, fund_type, amount;
    stream >> account_id >> fund_type >> amount;
    Transaction transaction(type, account_id, fund_type, amount);
    return transaction;
}

Transaction JollyBanker::InitTransferTransaction(char type, istringstream &stream){
    int account_id, fund_type, transfer_account_id, transfer_fund_type, amount;
    stream >> account_id >> fund_type >> transfer_account_id >> transfer_fund_type >> amount;
    Transaction transaction(type, account_id, fund_type, transfer_account_id, transfer_fund_type, amount);
    return transaction;
}

Transaction JollyBanker::InitAccountHistoryTransaction(char type, istringstream &stream){
    int account_id;
    stream >> account_id;
    Transaction transaction(type, account_id);
    return transaction;
}

Transaction JollyBanker::InitFundHistoryTransaction(char type, istringstream &stream){
    int account_id, fund_type;
    stream >> account_id >> fund_type;
    Transaction transaction(type, account_id, fund_type);
    return transaction;
}

Transaction JollyBanker::InitOpenTransaction(char type, istringstream &stream){
    int account_id;
    string first_name, last_name;
    stream >> account_id >> last_name >> first_name;
    Transaction transaction(type, account_id, first_name, last_name);
    return transaction;
}

bool JollyBanker::Process(){
    bool process_results = true;
    while (!transaction_list_.empty()) {
        Transaction transaction = transaction_list_.front();
        transaction_list_.pop();
        switch (transaction.type()) {
            case 'D': {
                process_results = ProcessDepositTransaction(transaction);
                break;
            }
            case 'W': {
                process_results = ProcessWithdrawTransaction(transaction);
                break;
            }
            case 'T': {
                process_results = ProcessTransferTransaction(transaction);
                break;
            }
            case 'A': {
                process_results = ProcessAccountHistoryTransaction(transaction);
                break;
            }
            case 'F': {
                process_results = ProcessFundHistoryTransaction(transaction);
                break;
            }
            case 'O': {
                process_results = ProcessOpenTransaction(transaction);
                break;
            }
        }           
    }
    return process_results;
}

bool JollyBanker::ProcessDepositTransaction(Transaction &transaction){
    Account *account = nullptr;
    if(!accounts_.Retrieve(transaction.account_id(), account)){
        cerr << "ERROR: Account " << transaction.account_id() << " not found. Deposit refused." << endl;
        return false;
    }
    return account->Deposit(transaction);
}

bool JollyBanker::ProcessWithdrawTransaction(Transaction& transaction) {
    Account* account = nullptr;
    if (!accounts_.Retrieve(transaction.account_id(), account)) {
        cerr << "ERROR: Account " << transaction.account_id() << " not found. Withdrawl refused." << endl;
        return false;
    }
    if(!account->Withdraw(transaction, true)){
        cerr << "ERROR: Not enough funds to withdraw " << transaction.amount() << " from " << account->first_name() << " " << account->last_name() << " " << kFundNames[transaction.fund_type()] << endl;
        return false;
    }
    return true;
}

bool JollyBanker::ProcessTransferTransaction(Transaction &transaction){
    Account *source_account = nullptr;
    Account *target_account = nullptr;

    if(!accounts_.Retrieve(transaction.account_id(), source_account)) {
        cerr << "ERROR: Account " << transaction.account_id() << " not found. Transferal refused." << endl;
        return false;
    }

    if (!accounts_.Retrieve(transaction.transfer_account_id(), target_account)) {
        cerr << "ERROR: Account " << transaction.transfer_account_id() << " not found. Transferal refused." << endl;
        return false;
    }
    if(!source_account->Transfer(transaction, *target_account)){
        cerr << "ERROR: Not enough funds to transfer " << transaction.amount() << " from " << source_account->first_name() << " " << source_account->last_name() << " " << kFundNames[transaction.fund_type()] << endl;
        return false;
    }
    return true;
}

bool JollyBanker::ProcessAccountHistoryTransaction(Transaction &transaction){
    Account *account = nullptr;
    if(!accounts_.Retrieve(transaction.account_id(), account)){
        cerr << "ERROR: Account " << transaction.account_id() << " not found. Account history refused." << endl;
        return false;
    }
    account->DisplayAccountHistory();
    return true;
}

bool JollyBanker::ProcessFundHistoryTransaction(Transaction &transaction){
    Account *account = nullptr;
    if(!accounts_.Retrieve(transaction.account_id(), account)){
        cerr << "ERROR: Account " << transaction.account_id() << " not found. Fund history refused." << endl;
        return false;
    }
    account->DisplayFundHistory(transaction.fund_type());
    return true;
}

bool JollyBanker::ProcessOpenTransaction(Transaction &transaction){
    if(!accounts_.OpenAccount(transaction.account_id(), transaction.first_name(), transaction.last_name())){
        return false;
    }
    return true;
}

void JollyBanker::Display(){
    cout << "FINAL BALANCES" << endl;
    accounts_.Display();
}