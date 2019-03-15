#pragma once


#include "../Transaction.h"

class Tree {

public:

    struct TreeNode {

        char walletID[50];
        int value;
        int depth;
        int children;
        Transaction *transaction;
        TreeNode *left;
        TreeNode *right;

        TreeNode(char *walletID, int value, int depth = 0, Transaction *transaction = NULL);
        ~TreeNode();

        int add(int value, Transaction* transaction, int *new_transactions);
        int xrisi_avgi();
    };

private:

    char *bitcoinID;
    int total_transaction;
    TreeNode *root;


public:
    Tree(char *bitcoinID, char *walletID, int value);
    ~Tree();

    int getTotalTransaction();

    void addTransaction(int value, Transaction *transaction);

    int xrisi_avgi();

};

