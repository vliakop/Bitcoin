#pragma once


#include "Lists/BitcoinList.h"

class Wallet {

private:

    char walletID[50];
    int balance;
    BitcoinList *bitcoin_list;
    // TODO transaction list;

public:
    Wallet(char *walletID, int balance = 0);

    ~Wallet();

    const char *getWalletID() const;

    void setWalletID(char *walletID);

    int getBalance() const;

    void setBalance(int balance);

    BitcoinList *getBitcoin_list() const;

    void setBitcoin_list(BitcoinList *bitcoin_list);

    void addBitcoin(char *bitcoin_id, int value, int denomination);

    void print();

};

