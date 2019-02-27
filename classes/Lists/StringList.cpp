#include <iostream>
#include <cstring>
#include "StringList.h"

using namespace std;
StringList::StringNode::StringNode(char *s, StringList::StringNode *next) :next(next) {

    this->s = (char *) malloc(strlen(s) + 1);
    strcpy(this->s, s);
}

StringList::StringNode::~StringNode() {

    if (s != NULL) {
        free(s);
    }
    s = NULL;
}

StringList::StringList() : size(0), head(NULL) {}

StringList::~StringList() {

    StringList::StringNode *n = head;
    while (n != NULL) {
        head = head->next;
        delete n;
        n = head;
    }
}

void StringList::add(char *s) {

    StringList::StringNode *n = new StringNode(s, head);
    head = n;
    size += 1;
}

bool StringList::contains(char *word) {

    if (size == 0) {
        return false;
    }
    StringList::StringNode *n = head;
    while (n != NULL) {
        if (strcmp(n->s, word) == 0) {
            return true;
        }
        n = n->next;
    }
}

void StringList::print() {

    StringList::StringNode *n = head;
    while (n != NULL) {
        if (n->next != NULL) {
            cout<<n->s<<"-->";
        } else {
            cout<<n->s<<endl;
        }
        n = n->next;
    }
}