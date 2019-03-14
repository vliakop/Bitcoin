#include <iostream>
#include <cstring>
#include "./functions/main_functions.h"
#include "classes/Lists/StringList.h"
#include "classes/Bucket.h"

using namespace std;
int main(int argc, char *argv[]) {

    // TODO change static bitcoins, transactions strings to char *
    char bitcoins[] = "./bitCoinBalancesFile.txt";
    char transactions[] = "transactionsFile.txt";
    int bitcoin_value = 100, sender_entries, receiver_entries, bucket_size;
//    init_arguments(argc, argv, bitcoins, transactions, &bitcoin_value, &sender_entries, &receiver_entries, &bucket_size);

    HashTable *all_wallets = new HashTable();
    HashTable *sender_wallets = new HashTable();
    HashTable *receiver_wallets = new HashTable();
    StringList *coins = new StringList();
    StringList *trans = new StringList();
    FILE *fp = open_file(bitcoins);
    char buf[512];

    while (fgets(buf, 512, fp) != NULL) {
        wallet_parse(buf, bitcoin_value, all_wallets, coins);
    }

    close_file(fp);
    all_wallets->print();
//TODO    delete all_wallets;
    time_t tt = 0;
    fp = open_file(transactions);
    while (fgets(buf, 512, fp) != NULL) {
        transaction_parse(buf, trans, all_wallets, sender_wallets, receiver_wallets, &tt);
    }
    close_file(fp);

    return 0;
}