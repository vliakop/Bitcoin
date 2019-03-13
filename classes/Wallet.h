#pragma once


#include "Lists/BitcoinList.h"
#include "Lists/TransactionList.h"

class Wallet {

private:

    char walletID[50];
    int balance;
    BitcoinList *bitcoin_list;
    TransactionList *transaction_list;
    // TODO transaction list;

public:
    Wallet(char *walletID, int balance = 0);

    ~Wallet();

    char *getWalletID() ;

    void setWalletID(char *walletID);

    int getBalance() const;

    void setBalance(int balance);

    BitcoinList *getBitcoin_list() const;

    void setBitcoin_list(BitcoinList *bitcoin_list);

    void addBitcoin(char *bitcoin_id, int value, int denomination);

    void print();

    bool hasID(char *walletID);

};

