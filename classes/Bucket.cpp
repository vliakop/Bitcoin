#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Bucket.h"

using namespace std;

Bucket::Bucket(int byte_size, int record_size) {

    this->byte_size = byte_size;
    this->record_size = record_size;
    record_capacity = byte_size/record_size;
    records = 0;
    array = (char *) malloc(byte_size);
}

Bucket::~Bucket() {

    if (array != NULL) {
        free(array);
    }
}

bool Bucket::addRecord(Wallet *record) {

    if (records == record_capacity) {
        return false;
    }
    memcpy(array + records*record_size, &record, sizeof(Wallet*));
    records += 1;
    return true;
}

void Bucket::print() {

    cout<<"BUCKET PRINTING '"<<records<<"' records"<<endl;
    Wallet *w;
    for (int i = 0; i < records; i++) {
        memcpy(&w, array + i*record_size, sizeof(Wallet*));
        w->print();
    }
}