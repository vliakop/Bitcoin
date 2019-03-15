#include <cstring>
#include "main_functions.h"
#include "cli_parsers.h"
#include <iostream>

using namespace std;

void command_parser(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date) {

    char delim[] = " \t\n\r";
    char *token = strtok(line, delim);

    if (token == NULL) {
        cout<<"No command was given"<<endl;
        return;
    }

    if (strncmp(token, "requestTransaction", strlen(token)) == 0) {
        token = strtok(NULL, "\n");
        request_transaction_handler(token, trans, all_wallets, senders, receivers, latest_date);
    } else if (strcmp(token, "requestTransactions") == 0) {
        token = strtok(NULL, "\n");
        char *pch = strchr(token, ';');
        if (pch == NULL) {  // Diabazoume apo arxeio
            request_transactions_file_handler(token, trans, all_wallets, senders, receivers, latest_date);
        } else {
            request_transactions_handler(token, trans, all_wallets, senders, receivers, latest_date);
        }
    } else if (strcmp(token, "findEarnings") == 0) {
        token = strtok(NULL, "\n");
        find_earnings_handler(token, receivers);
    } else if (strcmp(token, "findPayments") == 0) {
        token = strtok(NULL, "\n");
        find_payments_handler(token, senders);
    } else if(strcmp(token, "walletStatus") == 0) {
        token = strtok(NULL, "\n");
        wallet_status_handler(token, all_wallets);
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

    int id = trans->getMax() + 1;
    char transaction_id[128];   // TODO readme.
    memset(transaction_id, 0, 128);
    sprintf(transaction_id, "%d", id);
    char *command = (char *)malloc(strlen(transaction_id) + strlen(line) + 2);
    strcpy(command, transaction_id);
    strcat(command, " ");
    strcat(command, line);
    transaction_parse(command, trans, all_wallets, senders, receivers, latest_date);
    free(command);
}

void request_transactions_handler(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date) {

    if (line == NULL) {
        cout<<"No args for request-transactions command"<<endl;
        return;
    }

    char delims[] = ";";
    char command[1024];
    int size;
    strcpy(command, line);
    char *token = strtok(command, delims);
    while (token != NULL) {
        size = strlen(token);
        request_transaction_handler(token, trans, all_wallets, senders, receivers, latest_date);
        strcpy(command, command + size + 1);   // Problima me tin strtok: kaleitai stin epomeni sinartisi
        token = strtok(command, delims);
    }
    cout<<"No more valid request transaction commands given."<<endl;
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

void find_earnings_handler(char *line, HashTable *receivers) {

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
    strcpy(walletID, token);

    char time1[6];
    char time2[6];
    char year1[11];
    char year2[11];

    token = strtok(NULL, delims);
    if (token == NULL) {
        findEarnings_all(walletID, receivers);
    } else {
        char *pch = strchr(token, ':');
        if (pch == NULL) {  // year-only search: xreiazomai akoma ena token
            pch = strchr(token, '-');   // Elegxos oti einai imerominia
            if (pch == NULL) {
                cout<<"Wrong findEarnings command given. Expected time or date but none given. Cannot execute"<<endl;
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
                cout<<"Wrong findEarnings command given. Expected second date but none given. Cannot execute"<<endl;
                return;
            }
            strncpy(year2, token, 11);
            findEarnings_date(walletID, year1, year2, receivers);
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
                cout<<"findPayments time "<<time1<<" "<<time2<<endl;
                findEarnings_time(walletID, time1, time2, receivers);
                return;
            } else {    // full-time-search
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
                findEarnings_full(walletID, time1, year1, time2, year2, receivers);
                return;
            }

        }
    }
}

void find_payments_handler(char *line, HashTable *senders) {

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
    strcpy(walletID, token);

    char time1[6];
    char time2[6];
    char year1[11];
    char year2[11];

    token = strtok(NULL, delims);
    if (token == NULL) {
        findPayments_all(walletID, senders);
    } else {
        char *pch = strchr(token, ':');
        if (pch == NULL) {  // year-only search: xreiazomai akoma ena token
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
            findPayments_date(walletID, year1, year2, senders);
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
                cout<<"findPayments time "<<time1<<" "<<time2<<endl;
                findPayments_time(walletID, time1, time2, senders);
                return;
            } else {    // full-time-search
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
                findPayments_full(walletID, time1, year1, time2, year2, senders);
                return;
            }

        }
    }
}

void wallet_status_handler(char *line, HashTable *all_wallets) {

    if (line == NULL) {
        cout<<"No args for wallet-status command"<<endl;
        return;
    }
    char *walletID = strtok(line, "\n\t\r ");
    if (walletID == NULL) {
        cout<<"Expected walletID but none given. Command cannot be executed"<<endl;
        return;
    }
    walletStatus(walletID, all_wallets);
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