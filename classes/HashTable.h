#pragma once


#include "Lists/BucketList.h"

class HashTable {

private:

    BucketList **table;
    unsigned long size;

public:

    HashTable(unsigned long size = 5); // TODO change to 97

    ~HashTable();

    unsigned long hash(char *str);

    bool contains(Wallet *wallet);

    void add(Wallet *wallet);

    void print();

};

