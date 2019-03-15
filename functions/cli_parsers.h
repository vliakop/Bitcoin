#pragma once

bool command_parser(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date, BitcoinTreeList *btl);

void request_transaction_handler(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date, BitcoinTreeList *btl);

void request_transactions_handler(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date, BitcoinTreeList *btl);

void request_transactions_file_handler(char *line, StringList *trans, HashTable *all_wallets, HashTable *senders, HashTable *receivers, time_t *latest_date, BitcoinTreeList *btl);

void find_earnings_handler(char *line, HashTable *receivers);

void find_payments_handler(char *line, HashTable *senders);

void wallet_status_handler(char *line, HashTable *all_wallets);

void bitcoin_status_handler(char *line, BitcoinTreeList *btl);

void tracecoin_status_handler(char *line, BitcoinTreeList *btl);

void exit_handler();