#pragma once


#include "../Transaction.h"
#include "../Tree/Tree.h"

class BitcoinTreeList {

private:

    struct BTLNode {

        char *bitcoinID;
        Tree *bitconTree;
        BTLNode *next;

        BTLNode(char *bitcoinID, char* walletID, int value, BTLNode *next = NULL);
        ~BTLNode();
    };

    BTLNode *head;
    int size;

public:
    BitcoinTreeList();

    ~BitcoinTreeList();

    void add(char *bitcoinID, char *walletID, int bitcoin_value);

    void addTransaction(char *bitcoinID, Transaction *transaction);

    int getTransactions(char *bitcoinID);

    int xrisi_avgi(char *bitcoinID);
};

