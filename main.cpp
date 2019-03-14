#include <iostream>
#include <cstring>
#include "./functions/main_functions.h"
#include "classes/Lists/StringList.h"
#include "classes/Bucket.h"
#include "functions/cli_parsers.h"
#include "classes/Lists/BitcoinTreeList.h"

using namespace std;
int main(int argc, char *argv[]) {


//    return 0;

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
    BitcoinTreeList *btl = new BitcoinTreeList();

    /* Bitcoins */
    FILE *fp = open_file(bitcoins);
    char buf[512];
    while (fgets(buf, 512, fp) != NULL) {
        wallet_parse(buf, bitcoin_value, all_wallets, coins, btl);
    }
    close_file(fp);
 //   all_wallets->print();

    /* Transactions */
    time_t tt = 0;
    memset(&tt, 0, sizeof(time_t));
    fp = open_file(transactions);
    while (fgets(buf, 512, fp) != NULL) {
        transaction_parse(buf, trans, all_wallets, sender_wallets, receiver_wallets, &tt);
    }
    close_file(fp);

    /* Commandline */
    char commands[] = "commands.txt";
    char command[1024];

    cout<<"Give Command: ";
    while (fgets(command, 1024, stdin) != NULL) {
        command_parser(command, trans, all_wallets, sender_wallets, receiver_wallets, &tt);
        memset(command, 0, 1024);
        cout<<endl<<"Give Command: ";
    }


    /* Thanatos */
    delete all_wallets;
    delete sender_wallets;
    delete receiver_wallets;
    delete coins;
    delete trans;

return 0;
}