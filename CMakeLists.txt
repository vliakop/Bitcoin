cmake_minimum_required(VERSION 3.13)
project(Cryptocurrency)

set(CMAKE_CXX_STANDARD 98)

add_executable(Cryptocurrency main.cpp functions/main_functions.h functions/main_functions.cpp classes/Bitcoin.cpp classes/Bitcoin.h classes/Lists/BitcoinList.cpp classes/Lists/BitcoinList.h classes/Lists/StringList.cpp classes/Lists/StringList.h classes/Wallet.cpp classes/Wallet.h classes/Bucket.cpp classes/Bucket.h classes/Lists/BucketList.cpp classes/Lists/BucketList.h classes/HashTable.cpp classes/HashTable.h classes/Transaction.cpp classes/Transaction.h classes/Lists/TransactionList.cpp classes/Lists/TransactionList.h functions/cli_parsers.cpp functions/cli_parsers.h classes/Tree/Tree.cpp classes/Tree/Tree.h classes/Lists/BitcoinTreeList.cpp classes/Lists/BitcoinTreeList.h)