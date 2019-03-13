#pragma once

#include <cstddef>
#include "../Bitcoin.h"

class BitcoinList {

public:

    struct BitcoinNode {

        Bitcoin *bitcoin;
        BitcoinNode *previous;
        BitcoinNode *next;

        BitcoinNode(char *bitcoin_id, int bitcoin_value, int denomination, BitcoinNode *previous = NULL, BitcoinNode *next = NULL);
        ~BitcoinNode();
    };

private:

    BitcoinNode *head;
    BitcoinNode *tail;
    int size;

public:

    BitcoinList();
    BitcoinList(BitcoinList *bitcoinList);
    ~BitcoinList();

    BitcoinNode *getHead() const;

    void setHead(BitcoinNode *head);

    BitcoinNode *getTail() const;

    void setTail(BitcoinNode *tail);

    int getSize() const;

    void setSize(int size);

    bool add(char *bitcoin_id, int bitcoin_value, int denomination);

    void update_coin(char *bitcoin_id, int denomination);

    void print();

    bool contains(char *bitcoin_id);

//    Bitcoin* removeFromStart();
//
//    Bitcoin* removeFromEnd();
//
//    Bitcoin* removeBitcoinWithId(int id);
//
//    void print();



};



