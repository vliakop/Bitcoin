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

Tree::TreeNode::~TreeNode() {;}

Tree::Tree(char *bitcoinID, char *walletID, int value) {

    this->bitcoinID = (char *) malloc(strlen(bitcoinID) + 1);
    strcpy(this->bitcoinID, bitcoinID);
    this->total_transaction = 0;
    this->root = new TreeNode(walletID, value);
}

Tree::~Tree() {
    //TODO destructor
}

int Tree::TreeNode::add(int value, Transaction *transaction, int *new_transactions) {

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
            *new_transactions = *new_transactions + 1;
            return remainder;
        } else {
            if (this->left != NULL) {
                int done = left->add(value, transaction, new_transactions);
                if (done > 0) {
                    if (this->right != NULL) {
                        done = right->add(done, transaction, new_transactions);
                    }
                }
            }
        }
    } else { // An den eimai o kombos pou psaxneis
        if (this->left != NULL) {
            int done = left->add(value, transaction, new_transactions);
            if (done > 0) {
                if (this->right != NULL) {
                    done = right->add(done, transaction, new_transactions);
                }
            }
        }
    }
}


void Tree::addTransaction(int value, Transaction *transaction) {

    root->add(value, transaction, &total_transaction);
}