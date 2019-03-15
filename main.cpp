#include <iostream>
#include <cstring>
#include "./functions/main_functions.h"
#include "classes/Lists/StringList.h"
#include "classes/Bucket.h"
#include "functions/cli_parsers.h"
#include "classes/Lists/BitcoinTreeList.h"

using namespace std;

int bucket_size;
int main(int argc, char *argv[]) {

//    char bitcoins[] = "./bitCoinBalancesFile.txt";
//    char transactions[] = "transactionsFile.txt";

    char *bitcoins, *transactions;
    int bitcoin_value = 100, sender_entries, receiver_entries;
    init_arguments(argc, argv, bitcoins, transactions, &bitcoin_value, &sender_entries, &receiver_entries, &bucket_size);

    HashTable *all_wallets = new HashTable(sender_entries);       // Ola ta wallets
    HashTable *sender_wallets = new HashTable(sender_entries);    // Ta wallets ton senders
    HashTable *receiver_wallets = new HashTable(receiver_entries);  // Ta wallets ton receivers
    StringList *coins = new StringList();   // I lista me ta kamena bitcoinIDs
    StringList *trans = new StringList();   // I lista me ta kamena transactionIDs
    BitcoinTreeList *btl = new BitcoinTreeList();   // Lista me ta dentra ton bitcoins

    /* Arxikopoiisi ton bitcoins */
    FILE *fp = open_file(bitcoins);
    char buf[512];
    while (fgets(buf, 512, fp) != NULL) {
        wallet_parse(buf, bitcoin_value, all_wallets, coins, btl);
    }
    close_file(fp);

    /* Arxikopoiisi se transactions */
    time_t tt = 0;
    memset(&tt, 0, sizeof(time_t));
    fp = open_file(transactions);
    while (fgets(buf, 512, fp) != NULL) {
        transaction_parse(buf, trans, all_wallets, sender_wallets, receiver_wallets, &tt, btl);
    }
    close_file(fp);

    /* User commands */
    char command[1024];
    bool cont = true;
    cout<<"Give Command: ";
    while ((fgets(command, 1024, stdin) != NULL) && cont == true) {
        cont = command_parser(command, trans, all_wallets, sender_wallets, receiver_wallets, &tt, btl);
        memset(command, 0, 1024);
        cout<<endl<<"Give Command: ";
    }


    /* Thanatos */
    free(bitcoins);
    free(transactions);
    delete all_wallets;
    delete sender_wallets;
    delete receiver_wallets;
    delete coins;
    delete trans;

return 0;
}