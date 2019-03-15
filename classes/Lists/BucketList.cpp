#include "BucketList.h"

BucketList::BucketNode::BucketNode(int bucket_size, int record_size, BucketList::BucketNode *next) {

    bucket = new Bucket(bucket_size, record_size);
    this->next = next;
}

BucketList::BucketNode::~BucketNode() {

    if (bucket != NULL) {
        delete  bucket;
    }
}

BucketList::BucketList() {

    head = tail = NULL;
    size = 0;
}

BucketList::~BucketList() {

    BucketList::BucketNode *n = head;
    while (n != NULL) {
        head = head->next;
        delete n;
        n = head;
        size--;
    }
}

BucketList::BucketNode *BucketList::getHead() const {
    return head;
}

void BucketList::setHead(BucketList::BucketNode *head) {
    BucketList::head = head;
}

BucketList::BucketNode *BucketList::getTail() const {
    return tail;
}

void BucketList::setTail(BucketList::BucketNode *tail) {
    BucketList::tail = tail;
}

int BucketList::getSize() const {
    return size;
}

void BucketList::setSize(int size) {
    BucketList::size = size;
}

void BucketList::addWallet(Wallet *wallet) {

    if (size == 0) {    // An den yparxei BucketNode, dimiourgise ena
        head = tail = new BucketList::BucketNode(bucket_size);
        size += 1;
    } else {            // Diaforetika
        if (tail->bucket->isFull()) {   // An o teleutaios sti lista einai adeios
            BucketList::BucketNode *n = new BucketList::BucketNode();   // Dimiourgise neo BucketNode
            tail->next = n; // Kane ton teleutaio proteleutaio
            tail = n;   // Kane ton kainourio teleutaio
            size += 1;
        }
    }
    tail->bucket->addRecord(wallet);    // Bale to wallet sto Bucket
}

bool BucketList::contains(char *walletID) {

    if (size == 0) {
        return false;
    }
    bool contain = false;
    BucketNode *n = head;
    while (n != NULL) {
        if (n->bucket->contains(walletID)) {
            contain = true;
            break;
        }
        n = n->next;
    }
    return contain;
}

Wallet* BucketList::getWallet(char *walletID) {

    if (size == 0) {
        return NULL;
    }
    BucketNode *n = head;
    while (n != NULL) {
        if (n->bucket->contains(walletID)) {
            return n->bucket->getWallet(walletID);
        }
    }
}

void BucketList::print() {

    BucketNode *n = head;
    while (n != NULL) {
        n->bucket->print();
        n = n->next;
    }

}