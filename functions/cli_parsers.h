#pragma once

void command_parser(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date);

void request_transaction_handler(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date);

void request_transactions_handler(char *line);

void request_transactions_file_handler(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date);

void find_earnings_handler(char *line, HashTable *receivers);

void find_payments_handler(char *line, HashTable *senders);

void wallet_status_handler(char *line, HashTable *all_wallets);

void bitcoin_status_handler(char *line);

void tracecoin_status_handler(char *line);

void exit_handler();