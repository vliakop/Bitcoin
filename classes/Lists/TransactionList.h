#pragma once


#include "../Transaction.h"

class TransactionList {

public:

    struct TransactionNode{

        Transaction *transaction;
        TransactionNode *next;

        TransactionNode(Transaction *transaction, TransactionNode *next = NULL);
        ~TransactionNode();
    };

private:

    TransactionNode *head;
    TransactionNode *tail;
    int size;

public:

    TransactionList();
    TransactionList(TransactionList *list);
    ~TransactionList();

    TransactionNode *getHead() const;

    void setHead(TransactionNode *head);

    TransactionNode *getTail() const;

    void setTail(TransactionNode *tail);

    int getSize() const;

    void setSize(int size);

    Transaction* add(Transaction *transaction);
};

