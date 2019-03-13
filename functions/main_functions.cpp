#include "main_functions.h"
#include "../classes/Bitcoin.h"
#include "../classes/Wallet.h"
#include "../classes/HashTable.h"
#include "../classes/Transaction.h"
#include "../classes/Lists/StringList.h"
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
        exit(1);
    }
    return fp;
}


bool close_file(FILE *fp) {
    fclose(fp);
}


void wallet_parse(char *line, int bitcoin_value, HashTable *hashTable, StringList *bitcoinIDs) {

    char *token;
    char delim[] = " \n\r\t";

    token = strtok(line, delim);
    if (token == NULL) {
        cout<<"Error in wallet parsing. No walletId given. Now exiting"<<endl;
        exit(1);
    }
    Wallet *wallet = new Wallet(token);
    token = strtok(NULL, delim);
    while (token != NULL) { // Extract all bitcoin ids
        if (bitcoinIDs->contains(token) == false) {
            wallet->addBitcoin(token, bitcoin_value, bitcoin_value);
            bitcoinIDs->add(token);
        } else {
            cout<<"Bitcoin with id '"<<token<<"' already exists. Now exiting"<<endl;
            exit(1);
        }
        token = strtok(NULL, delim);
    }
    hashTable->add(wallet);
    // TODO PROSOXI: an den ginoun edo delete, prepei na ta kanei delete sto Bucket
}


void transaction_parse(char *line) {
    // TODO if token != NULL se ka8e strtok
    char id[15];
    char sender[50];
    char receiver[50];
    int value;

    char *token;
    char delim[] = " \n\t\r";

    token = strtok(line, delim);    // id
    strcpy(id, token);

    token = strtok(NULL, delim);
    if (token == NULL) {
        cout<<"SenderWalletId was needed. Now exiting"<<endl;
        exit(1);
    }
    strcpy(sender, token);

    token = strtok(NULL, delim);
    if (token == NULL) {
        cout<<"SenderWallerID was needed. Now exiting"<<endl;
        exit(1);
    }
    strcpy(receiver, token);

    token = strtok(NULL, delim);
    if (token == NULL) {
        cout<<"Value was needed. Now exiting"<<endl;
    }
    value = atoi(token);
    if (value < 0) {
        cout<<"Invalid value of bitcoin transfer"<<endl;
        exit(1);
    }

    token = strtok(NULL, "\n\r");
    char buf[255];
    if (token == NULL) {
        time_t rawtime;
        time(&rawtime); // Current time to time_t
        struct tm *tmptr;
        tmptr = localtime(&rawtime);    // time_t to struct tm
        strftime(buf, 255, "%d-%m-%Y %R", tmptr);   // struct tm to string
    } else {
        strcpy(buf, token);
    }

    cout<<"Date is '"<<buf<<"'"<<endl;
    // TODO checks (1) dates are ok, (2) sender exists + has balance, (3) receiver exists
    // TODO (4) kataxoriseis sta hashtables
    Transaction *trans = new Transaction(id, sender, receiver, value, buf);
    trans->print();
}