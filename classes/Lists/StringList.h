#pragma once


#include <cstdlib>

class StringList {

private:

    struct StringNode {
        char *s;
        StringNode *next;

        StringNode(char *s, StringNode *next = NULL);
        ~StringNode();
    };

    StringNode *head;
    int size;

public:

    StringList();
    ~StringList();
    void add(char *s);
    bool contains(char *word);
    void print();


};



