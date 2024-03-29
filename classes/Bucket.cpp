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
        Wallet *w = NULL;

        // Prospelasi ton eggrafon
        for (int i = 0; i < records; i++) {
            memcpy(&w, array + i * record_size, sizeof(Wallet *));
            delete w;
        }
        free(array);
    }
}

void Bucket::addRecord(Wallet *record) {

    if (records == record_capacity) {
        return;
    }
    // Pros8iki stin proti eleu8eri 8esi
    memcpy(array + records*record_size, &record, sizeof(Wallet*));
    records += 1;
}

void Bucket::print() {

    cout<<"Printing Bucket '"<<records<<"' records"<<endl;
    Wallet *w;
    for (int i = 0; i < records; i++) {
        memcpy(&w, array + i*record_size, sizeof(Wallet*));
        if(w == NULL) {
            return;
        }
        w->print();
    }
}

bool Bucket::isFull() {

    if (records == record_capacity) {
        return  true;
    }
    return false;
}

bool Bucket::contains(char *walletID) {

    Wallet *w;

    // Prospelasi ton eggrafon
    for (int i = 0; i < records; i++) {
        memcpy(&w, array + i*record_size, sizeof(Wallet*));
        if (w->hasID(walletID)) {
            return true;
        }
    }
    return false;
}

Wallet* Bucket::getWallet(char *walletID) {

    Wallet *w = NULL;

    // Prospelasi ton eggrafon
    for (int i = 0; i < records; i++) {
        memcpy(&w, array + i*record_size, sizeof(Wallet*));
        if (w->hasID(walletID)) {
            return w;
        }
    }
}