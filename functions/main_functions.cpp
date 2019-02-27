#include "main_functions.h"
#include "../classes/Bitcoin.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/* Extracts the values from argv and stores them in the arguments after it */
void init_arguments(int argc, char *argv[], char *bitcoins, char *transactions, int *bitcoin_value, int *sender_entries, int *receiver_entries, int *bucket_size) {

    if (argc != 13) {
        cout<<"Invalid number of arguments. Now exiting..."<<endl;
        exit(1);
    }
    for (int i = 1; i < 12; i += 2) {
        if (strcmp(argv[i], "-a") == 0) {
            bitcoins = (char *)malloc(strlen(argv[i + 1]) + 1);
            strcpy(bitcoins, argv[i + 1]);
        } else if (strcmp(argv[i], "-t") == 0) {
            transactions = (char *)malloc(strlen(argv[i + 1]) + 1);
            strcpy(transactions, argv[i + 1]);
        } else if (strcmp(argv[i], "-v") == 0) {
            *bitcoin_value = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-h1") == 0) {
            *sender_entries = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-h2") == 0) {
            *receiver_entries = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-b") == 0) {
            *bucket_size = atoi(argv[i + 1]);
        } else {
            cout<<"Invalid flag '" << argv[i] <<"' provided. Now exiting..."<<endl;
            exit(1);
        }
    }

    cout<<bitcoins<<endl<<transactions<<endl<<*bitcoin_value<<endl<<*sender_entries<<endl<<*receiver_entries<<endl<<*bucket_size<<endl;
}

FILE* open_file(char *filename) {

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        cout<<"Cannot open file '"<<filename<<"'"<<endl;
    }
    return fp;
}


bool close_file(FILE *fp) {
    fclose(fp);
}


void wallet_parse(char *line, int bitcoin_value) {

    char *token;
    char delim[] = " \n\t";
    token = strtok(line, delim);
    if (token == NULL) {
        cout<<"Error in wallet parsing. No walletId given. Now exiting"<<endl;
        exit(1);
    }
    while (token != NULL) {
        Bitcoin *bitcoin = new Bitcoin(token, bitcoin_value, bitcoin_value);
        token = strtok(NULL, delim);
        bitcoin->print();
        delete bitcoin;
    }
    // TODO (1) seperate walletId from bitcoinIds(first strtok), (2) create a wallet instead of just bitcoins
}

void transaction_parse(char *line) {

    char *token;
    char delim[] = " \n\t";
    token = strtok(line, delim);
    for (int i = 0; i < 4; i++) { // First 4 arguments are necessary. The 5th (date) might be missing
        if (token == NULL) {
            cout<<"Transaction parsing error"<<endl;
            exit(1);
        }
        cout<<token<<endl;
        token = strtok(NULL, delim);
    }
    if (token == NULL) {
        // TODO date stuff
    }
    // TODO add transaction functionality
}