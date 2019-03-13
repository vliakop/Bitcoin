#include <iostream>
#include <cstring>
#include <cstdlib>
#include "HashTable.h"

using namespace std;

HashTable::HashTable(unsigned long size) {

    this->size = size;
    table = new BucketList* [size];
    for (unsigned long i = 0; i < size; i++) {
        table[i] = new BucketList();
    }
}

HashTable::~HashTable() {

    for (unsigned long i = 0; i < size; i++) {
        delete table[i];
    }
    delete []table;
}

//djb2 hahs by Dan Bernstein
unsigned long HashTable::hash(char *str) {

    char *str2 = (char *)malloc(strlen(str) + 1);
    strcpy(str2, str);
    char *str3 = str2;
    unsigned long hash = 5381;
    int c;

    while (c = *str2++){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    hash = hash % size;
    cout<<"Hash for '"<<str<<"' is: "<<hash<<endl;
    free(str3);
    return hash;
}

bool HashTable::contains(Wallet *wallet) {

    char *walletID = wallet->getWalletID();
    unsigned long position = hash(walletID);
    if (table[position]->contains(walletID)) {
        return true;
    }
    return false;
}

bool HashTable::contains(char *walletId) {

    unsigned long position = hash(walletId);
    if (table[position]->contains(walletId)) {
        return true;
    }
    return false;
}


void HashTable::add(Wallet *wallet) {

    if (contains(wallet)) {
        cout<<"HashTable already has wallet with id '"<<wallet->getWalletID()<<"'"<<endl;
        return;
    }

    unsigned long position = hash(wallet->getWalletID());
    table[position]->addWallet(wallet);
}

void HashTable::print() {

    for (unsigned long i = 0; i < size; i++) {
        cout<<"Printing Hashtable position '"<<i<<"':"<<endl;
        table[i]->print();
    }
}

Wallet* HashTable::getWallet(char *walletId) {

    if(contains(walletId)) {
        unsigned long position = hash(walletId);
        return table[position]->getWallet(walletId);
    }
}