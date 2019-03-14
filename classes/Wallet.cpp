#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Wallet.h"

using namespace std;

Wallet::Wallet(char *walletID, int balance) {

    strcpy(this->walletID, walletID);
    bitcoin_list = new BitcoinList();
    this->balance = balance;
    transaction_list = new TransactionList();
}

Wallet::Wallet(Wallet *wallet) {

    strcpy(walletID, wallet->walletID);
    balance = wallet->balance;
    bitcoin_list = new BitcoinList(wallet->bitcoin_list);
    transaction_list = new TransactionList(wallet->transaction_list);
}

Wallet::~Wallet() {

    delete bitcoin_list;
    delete transaction_list;
    bitcoin_list = NULL;
    transaction_list = NULL;
}

char *Wallet::getWalletID()  {
    return walletID;
}

void Wallet::setWalletID(char *walletID) {
    strcpy(this->walletID, walletID);
}

int Wallet::getBalance() const {
    return balance;
}

void Wallet::setBalance(int balance) {
    Wallet::balance = balance;
}

BitcoinList *Wallet::getBitcoin_list() const {
    return bitcoin_list;
}

void Wallet::setBitcoin_list(BitcoinList *bitcoin_list) {
    Wallet::bitcoin_list = bitcoin_list;
}

void Wallet::copyBitcoin_list(BitcoinList *bitcoin_list) {

    if (bitcoin_list != NULL) {
        delete bitcoin_list;
    }
    bitcoin_list = new BitcoinList(bitcoin_list);
}

void Wallet::addBitcoin(char *bitcoin_id, int value, int denomination) {

    if (bitcoin_list->contains(bitcoin_id)) {
        bitcoin_list->update_coin(bitcoin_id, denomination);
    } else {
        bitcoin_list->add(bitcoin_id, value, denomination);
    }
    balance += denomination;
}

void Wallet::addTransaction(char *transaction_id, char *sender_id, char *receiver_id, int value, char *date) {

    transaction_list->add(new Transaction(transaction_id, sender_id, receiver_id, value, date));
}


void Wallet::print() {

    cout<<"Wallet with id: '"<<walletID<<"' and balance: '"<<balance<<"' has bitcoins: "<<endl;
    bitcoin_list->print();
    cout<<endl;
}

bool Wallet::hasID(char *walletID) {

    if (strcmp(walletID, this->walletID) == 0) {
        return true;
    }
    return false;
}