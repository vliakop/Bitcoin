#pragma once

#include <cstdio>
#include "../classes/Bucket.h"
#include "../classes/HashTable.h"
#include "../classes/Lists/StringList.h"
#include "../classes/Lists/BitcoinTreeList.h"

void init_arguments(int argc, char *argv[], char *bitcoins, char *transactions, int *bitcoin_value, int *sender_entries, int *receiver_entries, int *bucket_size);

FILE* open_file(char *filename);

bool close_file(FILE *fp);

time_t string_to_time_t(char *buf);

int mydifftime(struct tm tm1, struct tm tm2);

void wallet_parse(char *line, int bitcoin_value, HashTable *hashTable, StringList *bitcoinIDs, BitcoinTreeList *btl);

void transaction_parse(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date);

void create_transaction(char *transaction_id, char *sender_id, char *receiver_id, int value, char *date, StringList *transaction_ids, time_t *latest_date, HashTable *all_wallets, HashTable *senders, HashTable *receivers);

void transfer_coins(Wallet *sender, Wallet *receiver, int value);

void findEarnings_time(char *walletID, char *time1, char *time2, HashTable *receivers);

void findEarnings_date(char *walletID, char *date1, char *date2, HashTable *receivers);

void findEarnings_full(char *walletID, char *time1, char *date1, char *time2, char *date2, HashTable *receivers);

void findEarnings_all(char *walletID, HashTable *receivers);

void findPayments_time(char *walletID, char *time1, char *time2, HashTable *senders);

void findPayments_date(char *walletID, char *date1, char *date2, HashTable *senders);

void findPayments_full(char *walletID, char *time1, char *date1, char *time2, char *date2, HashTable *senders);

void findPayments_all(char *walletID, HashTable *senders);

void walletStatus(char *walletID, HashTable *all_wallets);



