#pragma once


#include "Lists/BitcoinList.h"
#include "Lists/TransactionList.h"

class Wallet {

private:

    char walletID[50];
    int balance;
    BitcoinList *bitcoin_list;
    TransactionList *transaction_list;

public:
    Wallet(char *walletID, int balance = 0);

    Wallet(Wallet *wallet);

    ~Wallet();

    char *getWalletID() ;

    void setWalletID(char *walletID);

    int getBalance() const;

    void setBalance(int balance);

    BitcoinList *getBitcoin_list() const;

    void setBitcoin_list(BitcoinList *bitcoin_list);

    TransactionList *getTransaction_list() const;

    void setTransaction_list(TransactionList *transaction_list);

    void copyBitcoin_list(BitcoinList *bitcoin_list);

    void addBitcoin(char *bitcoin_id, int value, int denomination);

    void addTransaction(char *transaction_id, char *sender_id, char *receiver_id, int value, char *date);

    void print();

    bool hasID(char *walletID);

};

