#include "BitcoinList.h"

BitcoinList::BitcoinNode::BitcoinNode(char *bitcoin_id, int bitcoin_value, int denomination,
                                      BitcoinList::BitcoinNode *previous, BitcoinList::BitcoinNode *next) {
    bitcoin = new Bitcoin(bitcoin_id, bitcoin_value, denomination);
    this->previous = previous;
    this->next = next;
}

BitcoinList::BitcoinNode::~BitcoinNode() {

    delete bitcoin;
}

BitcoinList::BitcoinList() {

    head = tail = NULL;
    size = 0;
}

BitcoinList::~BitcoinList() {

    BitcoinList::BitcoinNode *n;
    n = head;
    while (n != NULL) {
        head = head->next;
        delete n;
        n = head;
    }
}

BitcoinList::BitcoinNode *BitcoinList::getHead() const {
    return head;
}

void BitcoinList::setHead(BitcoinList::BitcoinNode *head) {
    this->head = head;
}

BitcoinList::BitcoinNode *BitcoinList::getTail() const {
    return tail;
}

void BitcoinList::setTail(BitcoinList::BitcoinNode *tail) {
    this->tail = tail;
}

int BitcoinList::getSize() const {
    return size;
}

void BitcoinList::setSize(int size) {
    this->size = size;
}

bool BitcoinList::add(char *bitcoin_id, int bitcoin_value, int denomination) {

    if (size == 0) {
        head = tail = new BitcoinList::BitcoinNode(bitcoin_id, bitcoin_value, denomination);
    } else {
        BitcoinList::BitcoinNode *n = new BitcoinList::BitcoinNode(bitcoin_id, bitcoin_value, denomination);
        tail->next = n;
        tail = n;
    }
    size += 1;
    return true;
}

void BitcoinList::print() {

    int i = size;
    BitcoinNode *n = head;
    while (size > 0) {
        n->bitcoin->print();
        n = n->next;
        size--;
    }
}