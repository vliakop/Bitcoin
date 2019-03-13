#include <cstring>
#include "BitcoinList.h"
#include <iostream>

using namespace std;

BitcoinList::BitcoinNode::BitcoinNode(char *bitcoin_id, int bitcoin_value, int denomination,
                                      BitcoinList::BitcoinNode *previous, BitcoinList::BitcoinNode *next) {
    bitcoin = new Bitcoin(bitcoin_id, bitcoin_value, denomination);
    this->previous = previous;
    this->next = next;
}

BitcoinList::BitcoinList(BitcoinList *bitcoinList) {

    BitcoinList::BitcoinNode *n = bitcoinList->getHead();
    while (n != NULL) {
        this->add(n->bitcoin->getBitcoin_id(), n->bitcoin->getValue(), n->bitcoin->getDenomination());
        n = n->next;
    }
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
        size--;
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

void BitcoinList::update_coin(char *bitcoin_id, int denomination) {

    BitcoinList::BitcoinNode *n = head;
    while (n != NULL) {
        if (strcmp(n->bitcoin->getBitcoin_id(), bitcoin_id) == 0) {
            n->bitcoin->setDenomination(n->bitcoin->getDenomination() + denomination);
            if (n->bitcoin->getDenomination() > n->bitcoin->getValue()) {
                cout<<"Bitcoin denomination shouldnt be higher than value"<<endl;
            }
        }
        n = n->next;
    }
}

void BitcoinList::print() {

    int i = size;
    BitcoinNode *n = head;
    while (i > 0) {
        n->bitcoin->print();
        n = n->next;
        i--;
    }
}

bool BitcoinList::contains(char *bitcoin_id) {

    BitcoinNode *n = head;
    while (n != NULL) {
        if (strcmp(n->bitcoin->getBitcoin_id(), bitcoin_id) == 0) {
            return true;
        }
        n = n->next;
    }
    return false;
}