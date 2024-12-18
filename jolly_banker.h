#ifndef JOLLY_BANKER_H_
#define JOLLY_BANKER_H_

#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include "bs_tree.h"
#include "transaction.h"

using namespace std;

class JollyBanker{
    public:
        JollyBanker();

        bool Init(string transactions_file);
        bool Process();
        void Display();

    private:
        queue<Transaction> transaction_list_;
        BSTree accounts_;

        Transaction InitDepositTransaction(char type, istringstream& stream);
        Transaction InitWithdrawTransaction(char type, istringstream &stream);
        Transaction InitTransferTransaction(char type, istringstream &stream);
        Transaction InitAccountHistoryTransaction(char type, istringstream &stream);
        Transaction InitFundHistoryTransaction(char type, istringstream &stream);
        Transaction InitOpenTransaction(char type, istringstream &stream);

        bool ProcessDepositTransaction(Transaction &transaction);
        bool ProcessWithdrawTransaction(Transaction& transaction);
        bool ProcessTransferTransaction(Transaction &transaction);
        bool ProcessAccountHistoryTransaction(Transaction &transaction);
        bool ProcessFundHistoryTransaction(Transaction &transaction);
        bool ProcessOpenTransaction(Transaction &transaction);

};
#endif