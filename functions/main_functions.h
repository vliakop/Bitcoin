#pragma once

#include <cstdio>

void init_arguments(int argc, char *argv[], char *bitcoins, char *transactions, int *bitcoin_value, int *sender_entries, int *receiver_entries, int *bucket_size);

FILE* open_file(char *filename);

bool close_file(FILE *fp);

void wallet_parse(char *line);

void transaction_parse(char *line);