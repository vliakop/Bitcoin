#include <cstring>
#include "cli_parsers.h"
#include <iostream>

using namespace std;

void command_parser(char *line) {

    char delim[] = " \t\n\r";
    char *token = strtok(line, delim);

    if (token == NULL) {
        cout<<"No command was given"<<endl;
        return;
    }

    if (strncmp(token, "requestTransaction", strlen(token)) == 0) {
        token = strtok(NULL, "\n");
        request_transactions_handler(token);
    } else if (strcmp(token, "requestTransactions") == 0) {
        token = strtok(NULL, "\n");
        char *pch = strrchr(line, ';'); // TODO uparxei error sto file logo ';'
        if (pch == NULL) {
            request_transactions_file_handler(token);
        } else {
            request_transactions_handler(token);
        }
    } else if (strcmp(token, "findEarnings") == 0) {
        token = strtok(NULL, "\n");
        find_earnings_handler(token);
    } else if (strcmp(token, "findPayments") == 0) {
        token = strtok(NULL, "\n");
        find_payments_handler(token);
    } else if(strcmp(token, "walletStatus") == 0) {
        token = strtok(NULL, "\n");
        wallet_status_handler(token);
    } else if(strcmp(token, "bitcoinStatus") == 0) {
        token = strtok(NULL, "\n");
        bitcoin_status_handler(token);
    } else if(strcmp(token, "traceCoin") == 0) {
        token = strtok(NULL, "\n");
        tracecoin_status_handler(token);
    } else if (strcmp(token, "exit") == 0) {
        // TODO handle
    } else {
        cout<<"Command '"<<line<<"' was not found"<<endl;
    }
}

void request_transaction_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for request-transaction command"<<endl;
        return;
    }

    cout<<"requestTransaction "<<line<<endl;
    //TODO functionality
}

void request_transactions_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for request-transactions command"<<endl;
        return;
    }

    cout<<"requestTransactions "<<line<<endl;
    //TODO functionality
}

void request_transactions_file_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for request-transactions-file command"<<endl;
        return;
    }

    cout<<"requestTransaction "<<line<<endl;
    //TODO functionality
}

void find_earnings_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for findEarnings command"<<endl;
        return;
    }

    cout<<"findEarnings "<<line<<endl;
    //TODO functionality
}

void find_payments_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for findPayments command"<<endl;
        return;
    }

    cout<<"findPayments "<<line<<endl;
    //TODO functionality
}

void wallet_status_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for wallet-status command"<<endl;
        return;
    }

    cout<<"wallet-status "<<line<<endl;
    //TODO functionality
}

void bitcoin_status_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for bitcoin-status command"<<endl;
        return;
    }

    cout<<"bitcoinStatus "<<line<<endl;
    //TODO functionality
}

void tracecoin_status_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for tracecoin-status command"<<endl;
        return;
    }

    cout<<"traceCoin "<<line<<endl;
    //TODO functionality
}