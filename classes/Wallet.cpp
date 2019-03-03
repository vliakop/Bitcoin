#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Wallet.h"

using namespace std;

Wallet::Wallet(char *walletID, int balance) {

    strcpy(this->walletID, walletID);
    bitcoin_list = new BitcoinList();
    this->balance = balance;
}

Wallet::~Wallet() {

    delete bitcoin_list;
}

const char *Wallet::getWalletID() const {
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

void Wallet::addBitcoin(char *bitcoin_id, int value, int denomination) {

    bitcoin_list->add(bitcoin_id, value, denomination);
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