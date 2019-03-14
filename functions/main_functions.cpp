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
    // TODO PROSOXI: an den ginoun edo delete, prepei na ta kanei delete sto Bucket ta wallets
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

void transaction_parse(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date){

    char id[15];
    char sender[50];
    char receiver[50];
    int value;

    char *token;
    char delim[] = " \n\t\r";

    token = strtok(line, delim);   // Pare to id tou transaction
    strcpy(id, token);

    token = strtok(NULL, delim);    // Pare to sender_wallet id
    if (token == NULL) {
        cout<<"SenderWalletId was needed. Now exiting"<<endl;
        exit(1);
    }
    strcpy(sender, token);

    token = strtok(NULL, delim);    // Pare to receiver wallet id
    if (token == NULL) {
        cout<<"ReceiverWallerID was needed. Now exiting"<<endl;
        exit(1);
    }
    strcpy(receiver, token);

    token = strtok(NULL, delim);    // Pare tin aksia se $
    if (token == NULL) {
        cout<<"Value was needed. Now exiting"<<endl;
    }
    value = atoi(token);
    if (value < 0) {
        cout<<"Invalid value of bitcoin transfer"<<endl;
        exit(1);
    }

    token = strtok(NULL, "\n\r");   // Pare to date
    char buf[255];
    if (token == NULL) {    // An de do8ei, bale to current_date
        time_t rawtime;
        time(&rawtime); // Current time to time_t
        struct tm *tmptr;
        tmptr = localtime(&rawtime);    // time_t to struct tm
        strftime(buf, 255, "%d-%m-%Y %R", tmptr);   // struct tm to string
    } else {
        strcpy(buf, token);
    }

    time_t date = string_to_time_t(buf);

    // TODO sto telos tis sunartisis *latest_date = date

    cout<<"Date is '"<<buf<<"'"<<endl;
    // TODO checks (1) dates are ok, (2) sender exists + has balance, (3) receiver exists
    // TODO (4) kataxoriseis sta hashtables
    Transaction *transa = new Transaction(id, sender, receiver, value, buf);
    transa->print();
    create_transaction(id, sender, receiver, value, buf, trans, latest_date, all_wallets, senders, receivers);
}

time_t string_to_time_t(char *buf) {

    struct tm tm;
    strptime(buf, "%d-%m-%Y %R", &tm);
    return mktime(&tm);
}

void create_transaction(char *transaction_id, char *sender_id, char *receiver_id, int value, char *date, StringList *transaction_ids, time_t *latest_date, HashTable *all_wallets, HashTable *senders, HashTable *receivers) {

    // Elegxos an uparxei idi to transaction basei id
    if (transaction_ids->contains(transaction_id)) {
        cout<<"Transaction with id '"<<transaction_id<<"' already exists. Not registering it"<<endl;
        return;
    }

    // Elegxos an o xronos tou transaction einai progenesteros tou teleutaiou transaction
    time_t current_date = string_to_time_t(date);
    double diff = difftime(current_date, *latest_date);
    if (diff < 0) {
        cout<<"Current date is prior to latest date. Cannot create the transaction"<<endl;
        return;
    }

    // Elegxos an uparxei to Wallet tou sender
    Wallet *all_sender = all_wallets->getWallet(sender_id);
    if (all_sender == NULL) {
        cout<<"Sender with id '"<<sender_id<<"' has not Wallet"<<endl;
        return;
    }

    // Elegxos an yparxei to Wallet tou receiver
    Wallet *all_receiver = all_wallets->getWallet(receiver_id);
    if (all_receiver == NULL) {
        cout<<"Receiver with id '"<<receiver_id<<"' has not Wallet"<<endl;
        return;
    }

    // Elegxos an to upoloipo tou sender eparkei
    if (all_sender->getBalance() < value) {
        cout<<"Sender with id '"<<sender_id<<"' does not have enough balance to transfer '"<<value<<"' to receiver with id '"<<receiver_id<<"'"<<endl;
        return;
    }

    // Pointer sto walletID sto senders HashTable
    Wallet *sender = senders->getWallet(sender_id);
    // TODO prosoxi sto ti kanei i parakato add: de 8elo na deixnei sto idio object me to allo hashtable. isos xreiastei na ftiakso neo Wallet
    if (sender == NULL) {
        senders->add(new Wallet(all_sender));
        sender = senders->getWallet(sender_id);
    }

    // Pointer sto walletID sto receivers HashTable
    Wallet *receiver = receivers->getWallet(receiver_id);
    // TODO prosoxi sto ti kanei i parakato add: de 8elo na deixnei sto idio object me to allo hashtable. isos xreiastei na ftiakso neo Wallet
    if (receiver == NULL) {
        receivers->add(new Wallet(all_receiver));
        receiver = receivers->getWallet(receiver_id);
    }

    // Kane metafora oson bitcoins xreiazetai
    transfer_coins(sender, receiver, value);

    // Ananeose ta balances sta wallets tou all_wallets hash table
    all_sender->setBalance(all_sender->getBalance() - value);
    all_receiver->setBalance(all_receiver->getBalance() + value);

    // Ftiakse transaction gia ton sender
    sender->addTransaction(transaction_id, sender_id, receiver_id, value, date);

    // Ftiakse transaction gia ton receiver
    receiver->addTransaction(transaction_id, sender_id, receiver_id, value, date);

    // Antigrafi tou sender bitcoin-list sto all_wallets
    all_sender->copyBitcoin_list(sender->getBitcoin_list());

    // Antigrafi tou receiver bitcoin-list sto all wallets
    all_receiver->copyBitcoin_list(receiver->getBitcoin_list());

}


void transfer_coins(Wallet *sender, Wallet *receiver, int value) {

    BitcoinList *sender_coins = sender->getBitcoin_list();
    BitcoinList::BitcoinNode *n = sender_coins->getHead();

    while (n != NULL && value > 0) {
        int denomination = n->bitcoin->getDenomination();
        if (denomination >= 0) {
            int transfer;
            if (denomination >= value) {
                transfer = value;
            } else {
                transfer = denomination;
            }
            // Afairesai to poso pou 8a metafer8ei apo to denomination
            n->bitcoin->setDenomination(denomination - transfer);

            // Enimerose to balance tou sender
            sender->setBalance(sender->getBalance() - transfer);

            // Kane metafora tou bitcoinID kai tou denomination ston receiver: metaferei bitcoin, denomination kai enimeronei to balance tou receiver
            receiver->addBitcoin(n->bitcoin->getBitcoin_id(), n->bitcoin->getValue(), transfer);

            // Enimerose to poso poy apomenei na metafer8ei
            value -= transfer;
        } else {
            n = n->next;
        }
    }
}