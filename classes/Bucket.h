#pragma once

extern int bucket_size;
#include "Wallet.h"

class Bucket {

private:

    int byte_size;
    int record_size;
    int record_capacity;
    int records;
    char *array;


public:

    Bucket(int byte_size, int record_size);

    ~Bucket();

    void addRecord(Wallet *record);

    void print();

    bool isFull();

    bool contains(char *walletID);

    Wallet* getWallet(char *walletID);

};

