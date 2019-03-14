#pragma once

#include <cstdio>
#include "../classes/Bucket.h"
#include "../classes/HashTable.h"
#include "../classes/Lists/StringList.h"

void init_arguments(int argc, char *argv[], char *bitcoins, char *transactions, int *bitcoin_value, int *sender_entries, int *receiver_entries, int *bucket_size);

FILE* open_file(char *filename);

bool close_file(FILE *fp);

void wallet_parse(char *line, int bitcoin_value, HashTable *hashTable, StringList *bitcoinIDs);

void transaction_parse(char *line);

void transaction_parse(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date);

time_t string_to_time_t(char *buf);

void create_transaction(char *transaction_id, char *sender_id, char *receiver_id, int value, char *date, StringList *transaction_ids, time_t *latest_date, HashTable *all_wallets, HashTable *senders, HashTable *receivers);

void transfer_coins(Wallet *sender, Wallet *receiver, int value);