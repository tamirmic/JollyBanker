#include "bs_tree.h"

BSTree::BSTree(){
    root_ = nullptr;
}

BSTree::~BSTree(){
    Clear(root_);
}

void BSTree::Clear(Node* node){
    if(node == nullptr){
        return;
    }

    Clear(node->left);
    Clear(node->right);

    delete node->p_account;
    delete node;
}

bool BSTree::Insert(Account* account){
    if(!account){
        return false;
    }

    Node* node = new Node; 
    node->p_account = account;

    if(root_ == nullptr){
        root_ = node;
        return true;
    }

    Node* current = root_;
    Node* parent = nullptr;

    while(current != nullptr){
        parent = current;
        if (account->id() < current->p_account->id()){
            current = current->left;
        }
        else if (account->id() > current->p_account->id()){
            current = current->right;
        }
        else{
            delete node;
            return false;
        }
    }

    if(account->id() < parent->p_account->id()){
        parent->left = node;
    }
    else{
        parent->right = node;
    }

    return true;
}

bool BSTree::OpenAccount(int account_id, string first_name, string last_name){
    if(account_id <= 0){
        cerr << "ERROR: Account " << account_id << " is invalid. Open account refused." << endl;
        return false;
    }
    Account *account = nullptr;
    if(Retrieve(account_id, account)){
        cerr << "ERROR: Account " << account_id << " is already open. Transaction refused." << endl;
        return false;
    }
    Insert(new Account(account_id, first_name, last_name));
    return true;
}

bool BSTree::Retrieve(int account_id, Account*& account) const{
    Node* current = root_;

    while(current != nullptr){
        if(account_id < current->p_account->id()){
            current = current->left;
        }
        else if (account_id > current->p_account->id()){
            current = current->right;
        }
        else{
            account = current->p_account;
            return true;
        }
    }
    
    account = nullptr;
    return false;
}

void BSTree::Display() const{
    RecursiveDisplay(root_);
}

void BSTree::RecursiveDisplay(Node* root) const{
    if(root == nullptr){
        return;
    }
    RecursiveDisplay(root->left);
    cout << *root->p_account;
    RecursiveDisplay(root->right);
}