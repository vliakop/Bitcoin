#include "TransactionList.h"

TransactionList::TransactionNode::TransactionNode(Transaction *transaction, TransactionList::TransactionNode *next) {

    this->transaction = transaction;
    this->next = next;
}

TransactionList::TransactionNode::~TransactionNode() {

    if (transaction != NULL) {
        delete transaction;
    }
}

TransactionList::TransactionList() {

    head = tail = NULL;
    size = 0;
}

TransactionList::TransactionList(TransactionList *list) {

    TransactionNode *n = list->getHead();
    while (n != NULL) {
        if (n->transaction != NULL) {
            this->add(new Transaction(n->transaction));
        }
        n = n->next;
    }
}

TransactionList::~TransactionList() {

    TransactionNode *n = head;
    while (head != NULL) {
        head = head->next;
        delete n;
        n = head;
        size--;
    }
}

TransactionList::TransactionNode *TransactionList::getHead() const {
    return head;
}

void TransactionList::setHead(TransactionList::TransactionNode *head) {
    TransactionList::head = head;
}

TransactionList::TransactionNode *TransactionList::getTail() const {
    return tail;
}

void TransactionList::setTail(TransactionList::TransactionNode *tail) {
    TransactionList::tail = tail;
}

int TransactionList::getSize() const {
    return size;
}

void TransactionList::setSize(int size) {
    TransactionList::size = size;
}


void TransactionList::add(Transaction *transaction) {

    if (size == 0) {
        head = tail = new TransactionList::TransactionNode(transaction);
    } else {
        TransactionNode *n = new TransactionNode(transaction);
        tail->next = n;
        tail = n;
    }
    size += 1;
}
