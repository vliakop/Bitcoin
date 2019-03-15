#include <cstring>
#include "Tree.h"
#include <iostream>
#include <cstdlib>


using namespace std;

Tree::TreeNode::TreeNode(char *walletID, int value, int depth, Transaction *transaction) {

    strcpy(this->walletID, walletID);
    this->value = value;
    this->depth = depth;
    this->transaction = transaction;
    children = 0;
    left = NULL;
    right = NULL;
}

Tree::TreeNode::~TreeNode() {

    if (left != NULL){
        delete left;
    }
    if (right != NULL) {
        delete right;
    }
}

Tree::Tree(char *bitcoinID, char *walletID, int value) {

    this->bitcoinID = (char *) malloc(strlen(bitcoinID) + 1);
    strcpy(this->bitcoinID, bitcoinID);
    this->total_transaction = 0;
    this->root = new TreeNode(walletID, value);
}

Tree::~Tree() {

    free(bitcoinID);
    delete root;
}

int Tree::TreeNode::add(int value, Transaction *transaction, int *new_transactions) {

    int done = value;
    char *sender = transaction->getSenderWalletID();
    char *receiver = transaction->getReceiverWalletID();

    if (strcmp(this->walletID, sender) == 0) {  // O kombos prepei exei idio onoma me ton sender
        if (this->children == 0) {  // An den yparxoun paidia
            int remainder = this->value - value;    // Elegxos an ta lefta tou kombou eparkoun gia ti metafora
            if (remainder < 0) {    // An den eparkoun
                remainder  = -remainder;    // Tote uparxei ypoloipo gia metafora
                value = this->value;    // Kai 8a metafer8oun osa exei o kombos
            }
            this->left = new TreeNode(receiver, value, this->depth + 1, transaction);   // Posa pire o receiver
            this->children++;
            if(remainder != 0) {  // An o sender de stelnei ola tou ta lefta
                this->right = new TreeNode(sender, this->value - value, this->depth + 1, transaction);  // Posa emeinan ston sender
                this->children++;
            }
            *new_transactions = *new_transactions + 1;  // Auksisi ton sunolikon transactions tou bitcoin
            return remainder;
        } else { // An uparxoun paidia
            if (this->left != NULL) {
                done = left->add(value, transaction, new_transactions); // Dokimase na baleis aristera
                if (done > 0) { // An uparxei ypoloipom dokimase deksia
                    if (this->right != NULL) {
                        done = right->add(done, transaction, new_transactions);
                    }
                }
            }
        }
    } else { // An den eimai o kombos pou psaxneis
        if (this->left != NULL) { // Dokimase na baleis aristera
            done = left->add(value, transaction, new_transactions);
            if (done > 0) { // An uparxei ypoloipom dokimase deksia
                if (this->right != NULL) {
                    done = right->add(done, transaction, new_transactions);
                }
            }
        }
    }
    return done;
}


void Tree::addTransaction(int value, Transaction *transaction) {

    root->add(value, transaction, &total_transaction);
}


int Tree::getTotalTransaction() {
    return total_transaction;
}

int Tree::TreeNode::xrisi_avgi() {

    if (children == 0) {    // An einai fullo epestrepse to value
        return value;
    }  else if (children == 1) {    // An yparxei ena paidi 8a einai to aristero poy simainei oti to unspent einai 0
        return  0;
    } else {
        return right->xrisi_avgi();
    }
}

int Tree::xrisi_avgi() {

    return root->xrisi_avgi();
}

// Gemizei tin transactionList me monadika transactions
void Tree::TreeNode::tracecoin(TransactionList *transactionList) {

    if (depth != 0) {  // I rize den prokyptei apo transaction
        if (transactionList->contains(this->transaction) == false) {
            transactionList->add(transaction);
        }
    }
    if (left != NULL){
        left->tracecoin(transactionList);
    }
    if (right != NULL) {
        right->tracecoin(transactionList);
    }
}

void Tree::tracecoin(TransactionList *transactionList) {

    root->tracecoin(transactionList);
}