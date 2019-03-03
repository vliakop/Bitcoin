#include <iostream>
#include <cstring>
#include "Transaction.h"

using namespace std;

Transaction:: Transaction(char *transactionID, char *senderWalletID, char *receiverWalletID, int value, char *date){

    strcpy(this->transactionID, transactionID);
    strcpy(this->senderWalletID, senderWalletID);
    strcpy(this->receiverWalletID, receiverWalletID);
    this->value = value;
    tm.tm_year = 0;
    tm.tm_mday = 0;
    tm.tm_mon = 0;
    tm.tm_wday = 0;
    tm.tm_yday = 0;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    strptime(date, "%d-%m-%Y %R", &(this->tm));
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