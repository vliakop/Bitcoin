#pragma once

#include <ctime>

class Transaction {

private:

    char transactionID[15];
    char senderWalletID[50];
    char receiverWalletID[50];
    int value;
    struct tm tm;

public:

    Transaction(char *transactionID, char *senderWalletID, char *receiverWalletID, int value, char *date);

    ~Transaction();

    char* getTransactionID();
    void setTransactionID(char *transactionID);
    char *getSenderWalletID();
    void setSenderWalletID(char *senderWalletID);
    char *getReceiverWalletID();
    void setReceiverWalletID(char *receiverWalletID);
    int getValue();
    void setValue(int value);
    struct tm getDate();
    void setDate(char *date);
    void dateToString();
    void print();

};

