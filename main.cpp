#include <iostream>
#include "./functions/main_functions.h"

int main(int argc, char *argv[]) {

    // TODO change static bitcoins, transactions strings to char *
    char bitcoins[] = "bitCoinBalancesFile.txt";
    char transactions[] = "transactionsFile.txt";
    int bitcoin_value = 100, sender_entries, receiver_entries, bucket_size;
//    init_arguments(argc, argv, bitcoins, transactions, &bitcoin_value, &sender_entries, &receiver_entries, &bucket_size);

    FILE *fp = open_file(bitcoins);
    char buf[512];

    while (fgets(buf, 512, fp) != NULL) {
        wallet_parse(buf, bitcoin_value);
    }

    close_file(fp);
    fp = open_file(transactions);
    while (fgets(buf, 512, fp) != NULL) {
        transaction_parse(buf);
    }
    close_file(fp);

    return 0;
}