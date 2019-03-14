#include <cstring>
#include <cstdlib>
#include "BitcoinTreeList.h"

BitcoinTreeList::BTLNode::BTLNode(char *bitcoinID, char *walletID, int value, BTLNode *next) {

    this->bitcoinID = (char *) malloc(strlen(bitcoinID) + 1);
    strcpy(this->bitcoinID, bitcoinID);
    this->bitconTree = new Tree(bitcoinID, walletID, value);
}

BitcoinTreeList::BTLNode::~BTLNode() {

    free(bitcoinID);
    delete bitconTree;
}

BitcoinTreeList::BitcoinTreeList() {

    this->size = 0;
    this->head = NULL;
}

BitcoinTreeList::~BitcoinTreeList() {

    BTLNode *n = head;
    while (n != NULL) {
        head = head->next;
        delete n;
        n = head;
    }
}

void BitcoinTreeList::add(char *bitcoinID, char *walletID, int bitcoin_value) {

    BTLNode *n = new BTLNode(bitcoinID, walletID, bitcoin_value, head);
    head = n;
    size += 1;
}

void BitcoinTreeList::addTransaction(char *bitcoinID, Transaction *transaction) {

    BTLNode *n = head;
    while (n != NULL) {
        if (strcmp(n->bitcoinID, bitcoinID) == 0) {
            n->bitconTree->addTransaction(transaction->getValue(), transaction);
        }
        n = n->next;
    }
}