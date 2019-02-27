#pragma once


class Bitcoin {

private:

    char *bitcoin_id;
    int value;
    int denomination;

public:

    Bitcoin(char *bitcoin_id, int value, int denomination);

    virtual ~Bitcoin();

    char *getBitcoin_id() const;

    void setBitcoin_id(char *bitcoin_id);

    int getValue() const;

    void setValue(int value);

    int getDenomination() const;

    void setDenomination(int denomination);

    void print();
};



