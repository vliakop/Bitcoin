#pragma once

#include <cstdio>
#include "../classes/Bucket.h"
#include "../classes/HashTable.h"

void init_arguments(int argc, char *argv[], char *bitcoins, char *transactions, int *bitcoin_value, int *sender_entries, int *receiver_entries, int *bucket_size);

FILE* open_file(char *filename);

bool close_file(FILE *fp);

void wallet_parse(char *line, int bitcoin_value, Bucket *bucket);

void wallet_parse(char *line, int bitcoin_value, HashTable *hashTable);

void transaction_parse(char *line);