#ifndef BS_TREE_H_
#define BS_TREE_H_

#include <iostream>
#include "account.h"
using namespace std;

class BSTree{
    public:
        BSTree();
        ~BSTree();

        bool Retrieve(int account_id, Account*& account) const;
        bool OpenAccount(int account_id, string first_name, string last_name);
        void Display() const;

    private:
        struct Node{
            Account* p_account = nullptr;
            Node* right = nullptr;
            Node* left = nullptr;
        };

        Node* root_ = nullptr;

        bool Insert(Account* account);
        void Clear(Node* node);
        void RecursiveDisplay(Node* root) const;
};
#endif