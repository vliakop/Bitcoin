#include <cstring>
#include <cstdlib>
#include "BitcoinTreeList.h"

BitcoinTreeList::BTLNode::BTLNode(char *bitcoinID, char *walletID, int value, BTLNode *next) {

    this->bitcoinID = (char *) malloc(strlen(bitcoinID) + 1);
    strcpy(this->bitcoinID, bitcoinID);
    this->bitconTree = new Tree(bitcoinID, walletID, value);
    this->next = next;
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

    BTLNode *n = new BTLNode(bitcoinID, walletID, bitcoin_value, this->head);
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

int BitcoinTreeList::getTransactions(char *bitcoinID) {

    BTLNode *n = head;
    while (n != NULL) {
        if (strcmp(n->bitcoinID, bitcoinID) == 0) {
            return n->bitconTree->getTotalTransaction();
        }
        n = n->next;
    }
    return 0;
}

// Epistrefei to value pou exei to pio deksi fullo
int BitcoinTreeList::xrisi_avgi(char *bitcoinID) {

    BTLNode *n = head;
    while (n != NULL) {
        if (strcmp(n->bitcoinID, bitcoinID) == 0) {
            return n->bitconTree->xrisi_avgi();
        }
        n = n->next;
    }
    return 0;
}

// Prosthetei eggrafes stin transactionList
void BitcoinTreeList::tracecoin(char *bitcoinID, TransactionList *transactionList) {

    BTLNode *n = head;
    while (n != NULL) {
        if (strcmp(n->bitcoinID, bitcoinID) == 0) {
            n->bitconTree->tracecoin(transactionList);
            break;
        }
        n = n->next;
    }
}

int BitcoinTreeList::getSize() {

    return size;
}

