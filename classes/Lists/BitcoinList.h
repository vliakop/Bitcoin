#pragma once

#include <cstddef>
#include "../Bitcoin.h"

class BitcoinList {

private:

    struct BitcoinNode {

        Bitcoin *bitcoin;
        BitcoinNode *previous;
        BitcoinNode *next;

        BitcoinNode(char *bitcoin_id, int bitcoin_value, int denomination, BitcoinNode *previous = NULL, BitcoinNode *next = NULL);
        ~BitcoinNode();
    };

    BitcoinNode *head;
    BitcoinNode *tail;
    int size;

public:

    BitcoinList();
    ~BitcoinList();

    BitcoinNode *getHead() const;

    void setHead(BitcoinNode *head);

    BitcoinNode *getTail() const;

    void setTail(BitcoinNode *tail);

    int getSize() const;

    void setSize(int size);

    bool add(char *bitcoin_id, int bitcoin_value, int denomination);

    void print();

//    Bitcoin* removeFromStart();
//
//    Bitcoin* removeFromEnd();
//
//    Bitcoin* removeBitcoinWithId(int id);
//
//    void print();



};



