#pragma once


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

    bool addRecord(Wallet *record);

    void print();

};

