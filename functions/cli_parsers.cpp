#include <cstring>
#include "main_functions.h"
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
        request_transaction_handler(token);
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

void request_transaction_handler(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date) {

    if (line == NULL) {
        cout<<"No args for request-transaction command"<<endl;
        return;
    }

//    cout<<"requestTransaction "<<line<<endl;
    transaction_parse(line, trans, all_wallets, senders, receivers, latest_date);
}

void request_transactions_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for request-transactions command"<<endl;
        return;
    }

    cout<<"requestTransactions "<<line<<endl;
    //TODO functionality
}

void request_transactions_file_handler(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date) {

    if (line == NULL) {
        cout<<"No args for request-transactions-file command"<<endl;
        return;
    }

    cout<<"requestTransaction "<<line<<endl;

    char *token = strtok(line, "\n\r");
    FILE *f = open_file(token);
    char buf[1024];
    while (fgets(buf, 1024, f) != NULL) {
        token = strtok(buf, ";");
        request_transaction_handler(token, trans, all_wallets, senders, receivers, latest_date);
    }
}

void find_earnings_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for findEarnings command"<<endl;
        return;
    }

    cout<<"findEarnings "<<line<<endl;

    char delims[] = " \n\r";
    char walletID[50];
    char *token = strtok(line, delims);
    if (token == NULL) {
        cout<<"findEarnings command cannot be executed. WalletID was expected but none provided"<<endl;
        return;
    }

    char time1[6];
    char time2[6];
    char year1[11];
    char year2[11];

    token = strtok(NULL, delims);
    if (token == NULL) {
        // TODO full-time-search
    } else {
        char *pch = strchr(token, ':');
        if (pch == NULL) {  // year-only seach: xreiazomai akoma ena token
            pch = strchr(token, '-');   // Elegxos oti einai imerominia
            if (pch == NULL) {
                cout<<"Wrong find-earnings command given. Expected time or date but none given. Cannot execute"<<endl;
                return;
            }
            strncpy(year1, token, 11);
            token = strtok(NULL, delims);
            if (token == NULL) {
                cout<<"Expected second date in year-only search findEarnings but none given. Aborting"<<endl;
                return;
            }
            pch = strchr(token , '-');
            if (pch == NULL) {
                cout<<"Wrong find-earnings command given. Expected second date but none given. Cannot execute"<<endl;
                return;
            }
            strncpy(year2, token, 11);
            // TODO year-only search
            return;
        } else {    // exo eite time-only search i full-time search me sugkekrimena dates
            strncpy(time1, token, 6);
            token = strtok(NULL, delims);
            if (token == NULL) {
                cout<<"Invalid number of arguments in findEarnings. More expected. Aborting"<<endl;
                return;
            }
            pch = strchr(token, ':');
            if (pch != NULL) {  // time-only search
                strncpy(time2, token, 6);
                // TODO time-only search
                return;
            } else {    // full-time-search
                token = strtok(NULL, delims);
                if (token == NULL) {
                    cout<<"Expected date1 in full-time findEarning but none given. Aborting"<<endl;
                    return;
                }
                strncpy(year1, token, 11);
                token = strtok(NULL, delims);
                if (token == NULL) {
                    cout<<"Expected time2 in full-time findEarnings but none given. Aborting"<<endl;
                    return;
                }
                strncpy(time2, token, 6);
                token = strtok(NULL, delims);
                if (token == NULL) {
                    cout<<"Expected year2 in full-time findEarnings but none given. Aborting"<<endl;
                    return;
                }
                strncpy(year2, token, 11);
                // TODO full-time search
                return;
            }

        }
    }
}

void find_payments_handler(char *line) {

    if (line == NULL) {
        cout<<"No args for findPayments command"<<endl;
        return;
    }

    cout<<"findPayments "<<line<<endl;

    char delims[] = " \n\r";
    char walletID[50];
    char *token = strtok(line, delims);
    if (token == NULL) {
        cout<<"findPayments command cannot be executed. WalletID was expected but none provided"<<endl;
        return;
    }

    char time1[6];
    char time2[6];
    char year1[11];
    char year2[11];

    token = strtok(NULL, delims);
    if (token == NULL) {
        // TODO full-time-search
    } else {
        char *pch = strchr(token, ':');
        if (pch == NULL) {  // year-only seach: xreiazomai akoma ena token
            pch = strchr(token, '-');   // Elegxos oti einai imerominia
            if (pch == NULL) {
                cout<<"Wrong find-payments command given. Expected time or date but none given. Cannot execute"<<endl;
                return;
            }
            strncpy(year1, token, 11);
            token = strtok(NULL, delims);
            if (token == NULL) {
                cout<<"Expected second date in year-only search findPayments but none given. Aborting"<<endl;
                return;
            }
            pch = strchr(token , '-');
            if (pch == NULL) {
                cout<<"Wrong find-payments command given. Expected second date but none given. Cannot execute"<<endl;
                return;
            }
            strncpy(year2, token, 11);
            // TODO year-only search
            return;
        } else {    // exo eite time-only search i full-time search me sugkekrimena dates
            strncpy(time1, token, 6);
            token = strtok(NULL, delims);
            if (token == NULL) {
                cout<<"Invalid number of arguments in findPayments. More expected. Aborting"<<endl;
                return;
            }
            pch = strchr(token, ':');
            if (pch != NULL) {  // time-only search
                strncpy(time2, token, 6);
                // TODO time-only search
                return;
            } else {    // full-time-search
                token = strtok(NULL, delims);
                if (token == NULL) {
                    cout<<"Expected date1 in full-time findPayments but none given. Aborting"<<endl;
                    return;
                }
                strncpy(year1, token, 11);
                token = strtok(NULL, delims);
                if (token == NULL) {
                    cout<<"Expected time2 in full-time findPayments but none given. Aborting"<<endl;
                    return;
                }
                strncpy(time2, token, 6);
                token = strtok(NULL, delims);
                if (token == NULL) {
                    cout<<"Expected year2 in full-time findPayments but none given. Aborting"<<endl;
                    return;
                }
                strncpy(year2, token, 11);
                // TODO full-time search
                return;
            }

        }
    }
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