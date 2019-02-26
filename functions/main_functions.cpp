#include "main_functions.h"
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

