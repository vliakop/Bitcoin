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

time_t string_to_time_t(char *buf) {

    struct tm tm = {0};
    strptime(buf, "%d-%m-%Y %R", &tm);
    return mktime(&tm);
}

void wallet_parse(char *line, int bitcoin_value, HashTable *hashTable, StringList *bitcoinIDs, BitcoinTreeList *btl) {

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
            btl->add(token, wallet->getWalletID(), bitcoin_value);
        } else {
            cout<<"Bitcoin with id '"<<token<<"' already exists. Now exiting"<<endl;
            exit(1);
        }
        token = strtok(NULL, delim);
    }

    hashTable->add(wallet);
    // TODO PROSOXI: an den ginoun edo delete, prepei na ta kanei delete sto Bucket ta wallets
}


void transaction_parse(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date){

    char id[15];
    char sender[50];
    char receiver[50];
    int value;

    char *token;
    char delim[] = " \n\t\r";

    /* transaction id */
    token = strtok(line, delim);   // Pare to id tou transaction
    strcpy(id, token);

    /* senderWalletID */
    token = strtok(NULL, delim);    // Pare to sender_wallet id
    if (token == NULL) {
        cout<<"SenderWalletId was needed. Now exiting"<<endl;
        exit(1);
    }
    strcpy(sender, token);

    /* receiverWalletID */
    token = strtok(NULL, delim);    // Pare to receiver wallet id
    if (token == NULL) {
        cout<<"ReceiverWallerID was needed. Now exiting"<<endl;
        exit(1);
    }
    strcpy(receiver, token);

    /* value */
    token = strtok(NULL, delim);    // Pare tin aksia se $
    if (token == NULL) {
        cout<<"Value was needed. Now exiting"<<endl;
        return;
    }
    value = atoi(token);
    if (value < 0) {
        cout<<"Invalid value of bitcoin transfer"<<endl;
        exit(1);
    }

    /* time and date */
    token = strtok(NULL, "\n\r");   // Pare to date
    char buf[255];
    if (token == NULL) {    // An de do8ei, bale to current_date
        time_t rawtime;
        time(&rawtime); // Current time to time_t
        struct tm *tmptr;
        tmptr = localtime(&rawtime);    // time_t to struct tm
        strftime(buf, 255, "%d-%m-%Y %R", tmptr);   // struct tm to string
    } else {
        strncpy(buf, token, 255);
    }

    /* Create the transaction */
    create_transaction(id, sender, receiver, value, buf, trans, latest_date, all_wallets, senders, receivers);

    /* Update the latest date */
    time_t next_date = string_to_time_t(buf);
    if (difftime(next_date, *latest_date) > 0) {
        *latest_date = next_date;
    }
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
        cout<<"Transaction date is prior to latest date. Cannot create the transaction with id '"<<transaction_id<<"'"<<endl;
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
    if (sender == NULL) {
        senders->add(new Wallet(all_sender));
        sender = senders->getWallet(sender_id);
    }

    // Pointer sto walletID sto receivers HashTable
    Wallet *receiver = receivers->getWallet(receiver_id);
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

    // Bale to transaction id sti lista me ta "kammena" id
    transaction_ids->add(transaction_id);

    // Antigrafi tou sender bitcoin-list sto all_wallets
    all_sender->copyBitcoin_list(sender->getBitcoin_list());

    // Antigrafi tou receiver bitcoin-list sto all wallets
    all_receiver->copyBitcoin_list(receiver->getBitcoin_list());

    cout<<"Transaction '"<<transaction_id<<" "<<sender_id<< " "<<receiver_id<<" "<<value<<" "<<date<<"' completed"<<endl;

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

void findEarnings_time(char *walletID, char *time1, char *time2, HashTable *receivers) {

    Wallet *wallet = receivers->getWallet(walletID);
    if (wallet == NULL) {
        cout<<"Wallet with id '"<<walletID<<"' has 0 earnings"<<endl;
        return;
    }

    int amount = 0;
    struct tm lowertm, uppertm, transactiontm;

    /* Make all struct tms default to 0 */
    memset(&lowertm, 0, sizeof(struct tm));
    memset(&uppertm, 0, sizeof(struct tm));
    memset(&transactiontm, 0, sizeof(struct tm));

    strptime(time1, "%R", &lowertm);
    strptime(time2, "%R", &uppertm);

    time_t upper = mktime(&uppertm);
    time_t lower = mktime(&lowertm);
    time_t tr;

    StringList *transactionIDs = new StringList();
    TransactionList *transactions = wallet->getTransaction_list();
    TransactionList::TransactionNode *n = transactions->getHead();
    while (n != NULL) {
        if (n->transaction == NULL) {
            cout<<"Got a null transaction in findEarnings time"<<endl;
            break;
        }
        transactiontm = n->transaction->getDate(); // Pare tin pliri imerominia
        transactiontm.tm_mday = 0;  // Krata mono ora kai lepta (ola ta alla einai 0)
        transactiontm.tm_mon = 0;
        transactiontm.tm_year = 0;
        tr = mktime(&transactiontm);   // Metatropi se xrono sustimatos
        if (lower <= tr && tr <= upper)  {
            transactionIDs->add(n->transaction->getTransactionID());
            amount += n->transaction->getValue();
        }
        memset(&transactiontm, 0, sizeof(struct tm));
        n = n->next;
    }
    cout<<"Total earnings for walletID '"<<walletID<<"' from '"<<time1<<"' to '"<<time2<<"' :"<<amount<<"$"<<endl;
    cout<<"Transactions involded: "<<endl;
    transactionIDs->print();
    delete transactionIDs;
}

void findEarnings_date(char *walletID, char *date1, char *date2, HashTable *receivers) {


    Wallet *wallet = receivers->getWallet(walletID);
    if (wallet == NULL) {
        cout<<"Wallet with id '"<<walletID<<"' has 0 earnings"<<endl;
        return;
    }

    int amount = 0;
    struct tm lowertm, uppertm, transactiontm;

    /* Make all struct tms default to 0 */
    memset(&lowertm, 0, sizeof(struct tm));
    memset(&uppertm, 0, sizeof(struct tm));
    memset(&transactiontm, 0, sizeof(struct tm));

    strptime(date1, "%d-%m-%Y", &lowertm);
    strptime(date2, "%d-%m-%Y", &uppertm);

    time_t upper = mktime(&uppertm);
    time_t lower = mktime(&lowertm);
    time_t tr;

    StringList *transactionIDs = new StringList();
    TransactionList *transactions = wallet->getTransaction_list();
    TransactionList::TransactionNode *n = transactions->getHead();
    while (n != NULL) {
        if (n->transaction == NULL) {
            cout<<"Got a null transaction in findEarnings time"<<endl;
            break;
        }
        transactiontm = n->transaction->getDate(); // Pare tin pliri imerominia
        transactiontm.tm_min = 0;  // Krata mono mera, mina kai etos (ola ta alla einai 0)
        transactiontm.tm_hour = 0;
        tr = mktime(&transactiontm);   // Metatropi se xrono sustimatos
        if (lower <= tr && tr <= upper)  {
            transactionIDs->add(n->transaction->getTransactionID());
            amount += n->transaction->getValue();
        }
        memset(&transactiontm, 0, sizeof(struct tm));
        n = n->next;
    }
    cout<<"Total earnings for walletID '"<<walletID<<"' from '"<<date1<<"' to '"<<date2<<"' :"<<amount<<"$"<<endl;
    cout<<"Transactions involded: "<<endl;
    transactionIDs->print();
    delete transactionIDs;
}

void findEarnings_full(char *walletID, char *time1, char *date1, char *time2, char *date2, HashTable *receivers) {
    Wallet *wallet = receivers->getWallet(walletID);
    if (wallet == NULL) {
        cout<<"Wallet with id '"<<walletID<<"' has 0 earnings"<<endl;
        return;
    }

    int amount = 0;
    struct tm lowertm, uppertm, transactiontm;

    /* Make all struct tms default to 0 */
    memset(&lowertm, 0, sizeof(struct tm));
    memset(&uppertm, 0, sizeof(struct tm));
    memset(&transactiontm, 0, sizeof(struct tm));

    char *fulldate1 = (char *) malloc(strlen(time1) + strlen(date1) + 2);
    strcpy(fulldate1, date1);
    strcat(fulldate1, " ");
    strcat(fulldate1, time1);

    char *fulldate2 = (char *) malloc(strlen(time2) + strlen(date2) + 2);
    strcpy(fulldate2, date2);
    strcat(fulldate2, " ");
    strcat(fulldate2, time2);

    strptime(fulldate1, "%d-%m-%Y %R", &lowertm);
    strptime(fulldate2, "%d-%m-%Y %R", &uppertm);

    time_t upper = mktime(&uppertm);
    time_t lower = mktime(&lowertm);
    time_t tr;

    StringList *transactionIDs = new StringList();
    TransactionList *transactions = wallet->getTransaction_list();
    TransactionList::TransactionNode *n = transactions->getHead();
    while (n != NULL) {
        if (n->transaction == NULL) {
            cout<<"Got a null transaction in findEarnings full"<<endl;
            break;
        }
        transactiontm = n->transaction->getDate(); // Pare tin pliri imerominia
        tr = mktime(&transactiontm);   // Metatropi se xrono sustimatos
        if (lower <= tr && tr <= upper) {
            transactionIDs->add(n->transaction->getTransactionID());
            amount += n->transaction->getValue();
        }
        memset(&transactiontm, 0, sizeof(struct tm));
        n = n->next;
    }
    cout<<"Total earnings for walletID '"<<walletID<<"' from '"<<fulldate1<<"' to '"<<fulldate2<<"' :"<<amount<<"$"<<endl;
    cout<<"Transactions involded: "<<endl;
    transactionIDs->print();
    free(fulldate1);
    free(fulldate2);
    delete transactionIDs;
}

void findEarnings_all(char *walletID, HashTable *receivers) {

    Wallet *wallet = receivers->getWallet(walletID);
    if (wallet == NULL) {
        cout<<"Wallet with id '"<<walletID<<"' has 0 earnings"<<endl;
        return;
    }

    int amount = 0;
    StringList *transactionIDs = new StringList();
    TransactionList *transactions = wallet->getTransaction_list();
    TransactionList::TransactionNode *n = transactions->getHead();
    while (n != NULL) {
        if (n->transaction == NULL) {
            cout<<"Got a null transaction in findEarnings full"<<endl;
            break;
        }
        transactionIDs->add(n->transaction->getTransactionID());
        amount += n->transaction->getValue();
        n = n->next;
    }
    cout<<"Total earnings for walletID '"<<walletID<<"' from 'start of time' until 'now': "<<amount<<"$"<<endl;
    cout<<"Transactions involded: "<<endl;
    transactionIDs->print();
    delete transactionIDs;

}

void findPayments_time(char *walletID, char *time1, char *time2, HashTable *senders) {

    Wallet *wallet = senders->getWallet(walletID);
    if (wallet == NULL) {
        cout<<"Wallet with id '"<<walletID<<"' has 0 payments"<<endl;
        return;
    }

    int amount = 0;
    struct tm lowertm, uppertm, transactiontm;

    /* Make all struct tms default to 0 */
    memset(&lowertm, 0, sizeof(struct tm));
    memset(&uppertm, 0, sizeof(struct tm));

    strptime(time1, "%R", &lowertm);
    strptime(time2, "%R", &uppertm);

    time_t upper = mktime(&uppertm);
    time_t lower = mktime(&lowertm);
    time_t tr;

    StringList *transactionIDs = new StringList();
    TransactionList *transactions = wallet->getTransaction_list();
    TransactionList::TransactionNode *n = transactions->getHead();
    while (n != NULL) {
        if (n->transaction == NULL) {
            cout<<"Got a null transaction in findPayments time"<<endl;
            break;
        }
        transactiontm = n->transaction->getDate(); // Pare tin pliri imerominia
        int hour = transactiontm.tm_hour;
        int min = transactiontm.tm_min;
        memset(&transactiontm, 0, sizeof(struct tm));
        transactiontm.tm_hour = hour;// Krata mono ora kai lepta (ola ta alla einai 0)
        transactiontm.tm_min = min;
        tr = mktime(&transactiontm);   // Metatropi se xrono sustimatos
        if (lower <= tr && tr <= upper) {
            transactionIDs->add(n->transaction->getTransactionID());
            amount += n->transaction->getValue();
        }
        n = n->next;
    }
    cout<<"Total payments for walletID '"<<walletID<<"' from '"<<time1<<"' to '"<<time2<<"' :"<<amount<<"$"<<endl;
    cout<<"Transactions involded: "<<endl;
    transactionIDs->print();
    delete transactionIDs;
}

void findPayments_date(char *walletID, char *date1, char *date2, HashTable *senders) {


    Wallet *wallet = senders->getWallet(walletID);
    if (wallet == NULL) {
        cout<<"Wallet with id '"<<walletID<<"' has 0 payments"<<endl;
        return;
    }

    int amount = 0;
    struct tm lowertm, uppertm, transactiontm;

    /* Make all struct tms default to 0 */
    memset(&lowertm, 0, sizeof(struct tm));
    memset(&uppertm, 0, sizeof(struct tm));
    memset(&transactiontm, 0, sizeof(struct tm));

    strptime(date1, "%d-%m-%Y", &lowertm);
    strptime(date2, "%d-%m-%Y", &uppertm);

    time_t upper = mktime(&uppertm);
    time_t lower = mktime(&lowertm);
    time_t tr;

    StringList *transactionIDs = new StringList();
    TransactionList *transactions = wallet->getTransaction_list();
    TransactionList::TransactionNode *n = transactions->getHead();
    while (n != NULL) {
        if (n->transaction == NULL) {
            cout<<"Got a null transaction in findPayments time"<<endl;
            break;
        }
        transactiontm = n->transaction->getDate(); // Pare tin pliri imerominia
        transactiontm.tm_min = 0;  // Krata mono mera, mina kai etos (ola ta alla einai 0)
        transactiontm.tm_hour = 0;
        tr = mktime(&transactiontm);   // Metatropi se xrono sustimatos
        if (lower <= tr && tr <= upper) {
            transactionIDs->add(n->transaction->getTransactionID());
            amount += n->transaction->getValue();
        }
        memset(&transactiontm, 0, sizeof(struct tm));
        n = n->next;
    }
    cout<<"Total payments for walletID '"<<walletID<<"' from '"<<date1<<"' to '"<<date2<<"' :"<<amount<<"$"<<endl;
    cout<<"Transactions involded: "<<endl;
    transactionIDs->print();
    delete transactionIDs;
}

void findPayments_full(char *walletID, char *time1, char *date1, char *time2, char *date2, HashTable *senders) {

    Wallet *wallet = senders->getWallet(walletID);
    if (wallet == NULL) {
        cout<<"Wallet with id '"<<walletID<<"' has 0 payments"<<endl;
        return;
    }

    int amount = 0;
    struct tm lowertm, uppertm, transactiontm;

    /* Make all struct tms default to 0 */
    memset(&lowertm, 0, sizeof(struct tm));
    memset(&uppertm, 0, sizeof(struct tm));
    memset(&transactiontm, 0, sizeof(struct tm));

    char *fulldate1 = (char *) malloc(strlen(time1) + strlen(date1) + 2);
    strcpy(fulldate1, date1);
    strcat(fulldate1, " ");
    strcat(fulldate1, time1);

    char *fulldate2 = (char *) malloc(strlen(time2) + strlen(date2) + 2);
    strcpy(fulldate2, date2);
    strcat(fulldate2, " ");
    strcat(fulldate2, time2);

    strptime(fulldate1, "%d-%m-%Y %R", &lowertm);
    strptime(fulldate2, "%d-%m-%Y %R", &uppertm);

    time_t upper = mktime(&uppertm);
    time_t lower = mktime(&lowertm);
    time_t tr;

    StringList *transactionIDs = new StringList();
    TransactionList *transactions = wallet->getTransaction_list();
    TransactionList::TransactionNode *n = transactions->getHead();
    while (n != NULL) {
        if (n->transaction == NULL) {
            cout<<"Got a null transaction in findPayments full"<<endl;
            break;
        }
        transactiontm = n->transaction->getDate(); // Pare tin pliri imerominia
        tr = mktime(&transactiontm);   // Metatropi se xrono sustimatos
        if (lower <= tr && tr <= upper) {
            transactionIDs->add(n->transaction->getTransactionID());
            amount += n->transaction->getValue();
        }
        memset(&transactiontm, 0, sizeof(struct tm));
        n = n->next;
    }
    cout<<"Total payments for walletID '"<<walletID<<"' from '"<<fulldate1<<"' to '"<<fulldate2<<"' :"<<amount<<"$"<<endl;
    cout<<"Transactions involded: "<<endl;
    transactionIDs->print();
    free(fulldate1);
    free(fulldate2);
    delete transactionIDs;
}

void findPayments_all(char *walletID, HashTable *senders) {

    Wallet *wallet = senders->getWallet(walletID);
    if (wallet == NULL) {
        cout<<"Wallet with id '"<<walletID<<"' has 0 payments"<<endl;
        return;
    }

    int amount = 0;
    StringList *transactionIDs = new StringList();
    TransactionList *transactions = wallet->getTransaction_list();
    TransactionList::TransactionNode *n = transactions->getHead();
    while (n != NULL) {
        if (n->transaction == NULL) {
            cout<<"Got a null transaction in findPayments all"<<endl;
            break;
        }
        transactionIDs->add(n->transaction->getTransactionID());
        amount += n->transaction->getValue();
        n = n->next;
    }
    cout<<"Total payments for walletID '"<<walletID<<"' from 'start of time' until 'now': "<<amount<<"$"<<endl;
    cout<<"Transactions involded: "<<endl;
    transactionIDs->print();
    delete transactionIDs;
}

void walletStatus(char *walletID, HashTable *all_wallets) {

    Wallet *wallet = all_wallets->getWallet(walletID);
    if (wallet == NULL) {
        cout<<"Wallet with id '"<<walletID<<"' doesn't exist. Cannot walletStatus"<<endl;
        return;
    }
    cout<<"Wallet with id '"<<walletID<<"' has total balance: "<<wallet->getBalance()<<"$"<<endl;
}