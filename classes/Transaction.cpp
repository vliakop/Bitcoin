#include <iostream>
#include <cstring>
#include "Transaction.h"

using namespace std;

Transaction:: Transaction(char *transactionID, char *senderWalletID, char *receiverWalletID, int value, char *date){

    strcpy(this->transactionID, transactionID);
    strcpy(this->senderWalletID, senderWalletID);
    strcpy(this->receiverWalletID, receiverWalletID);
    this->value = value;
    memset(&tm, 0, sizeof(tm));
    struct tm ttm;
    strptime(date, "%d-%m-%Y %R", &(ttm));
    this->tm.tm_mday = ttm.tm_mday;
    this->tm.tm_mon = ttm.tm_mon;
    this->tm.tm_year = ttm.tm_year;
    this->tm.tm_hour = ttm.tm_hour;
    this->tm.tm_min = ttm.tm_min;
}

Transaction::Transaction(Transaction *transaction) {

    strcpy(transactionID, transaction->transactionID);
    strcpy(senderWalletID, transaction->senderWalletID);
    strcpy(receiverWalletID, transaction->receiverWalletID);
    value = transaction->value;
    memcpy(&tm, &(transaction->tm), sizeof(struct tm));
}

Transaction::~Transaction() {

}


char* Transaction::getTransactionID() {
    return transactionID;
}

void Transaction::setTransactionID(char *transactionID) {
    strcpy(this->transactionID, transactionID);
}

char* Transaction::getSenderWalletID() {
    return senderWalletID;
}

void Transaction::setSenderWalletID(char *senderWalletID) {
    strcpy(this->senderWalletID, senderWalletID);
}

char* Transaction::getReceiverWalletID() {
    return receiverWalletID;
}

void Transaction::setReceiverWalletID(char *receiverWalletID) {
    strcpy(this->receiverWalletID, receiverWalletID);
}

int Transaction::getValue() {
    return value;
}

void Transaction::setValue(int value) {
    this->value = value;
}

struct tm Transaction::getDate() {
    return tm;
}

void Transaction::setDate(char *date) {
    strptime(date, "%d-%m-%Y %R", &(this->tm));
}

void Transaction::dateToString(){
    char buf[20];
    strftime(buf, 20, "%d-%m-%Y %R", &(this->tm));
    cout<<buf;
}

void Transaction::print() {
    cout<<"Transaction id: '"<<transactionID<<"' sender: '"<<senderWalletID<<"' receiver: '"<<receiverWalletID<<"' value: '"<<value<<"' date: '";
    dateToString();
    cout<<"'"<<endl;
}