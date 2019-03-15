#pragma once


#include "Lists/BucketList.h"

class HashTable {

private:

    BucketList **table;
    unsigned long size;

public:

    HashTable(unsigned long size = 5);

    ~HashTable();

    unsigned long hash(char *str);

    bool contains(Wallet *wallet);

    bool contains(char *walletId);

    void add(Wallet *wallet);

    void print();

    Wallet *getWallet(char *walledId);

};

