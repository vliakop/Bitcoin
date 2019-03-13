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