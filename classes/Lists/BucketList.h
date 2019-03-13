#pragma once


#include "../Bucket.h"

class BucketList {

private:

    struct BucketNode {

        Bucket *bucket;
        BucketNode *next;

       BucketNode(int bucket_size = 1000, int record_size = sizeof(Wallet *), BucketNode *next = NULL);
       ~BucketNode();
    };

    BucketNode *head;
    BucketNode *tail;
    int size;

public:

    BucketList();
    ~BucketList();

    BucketNode *getHead() const;

    void setHead(BucketNode *head);

    BucketNode *getTail() const;

    void setTail(BucketNode *tail);

    int getSize() const;

    void setSize(int size);

    void addWallet(Wallet *wallet);

    bool contains(char * walletID);

    Wallet* getWallet(char *walletID);

    void print();
};

