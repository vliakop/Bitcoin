#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Bitcoin.h"

using namespace std;

Bitcoin::Bitcoin(char *bitcoin_id, int value, int denomination) : value(value),
                                                                  denomination(denomination) {
    this->bitcoin_id = (char *)malloc(strlen(bitcoin_id) + 1);
    strcpy(this->bitcoin_id, bitcoin_id);
}

Bitcoin::~Bitcoin() {

    if (bitcoin_id != NULL) {
        free(bitcoin_id);
    }
}

char *Bitcoin::getBitcoin_id() const {
    return bitcoin_id;
}

void Bitcoin::setBitcoin_id(char *bitcoin_id) {
    free(this->bitcoin_id);
    this->bitcoin_id = (char *)malloc(strlen(bitcoin_id) + 1);
    strcpy(this->bitcoin_id, bitcoin_id);
}

int Bitcoin::getValue() const {
    return value;
}

void Bitcoin::setValue(int value) {
    this->value = value;
}

int Bitcoin::getDenomination() const {
    return denomination;
}

void Bitcoin::setDenomination(int denomination) {
    this->denomination = denomination;
}


void Bitcoin::print() {

    cout<<" Bitcoin id: "<<bitcoin_id<<endl;
}