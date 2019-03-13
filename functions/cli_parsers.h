#pragma once

void command_parser(char *line);

void request_transaction_handler(char *line);

void request_transactions_handler(char *line);

void request_transactions_file_handler(char *line);

void find_earnings_handler(char *line);

void find_payments_handler(char *line);

void wallet_status_handler(char *line);

void bitcoin_status_handler(char *line);

void tracecoin_status_handler(char *line);

void exit_handler();