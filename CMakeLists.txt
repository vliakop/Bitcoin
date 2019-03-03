cmake_minimum_required(VERSION 3.13)
project(Cryptocurrency)

set(CMAKE_CXX_STANDARD 98)

add_executable(Cryptocurrency main.cpp functions/main_functions.h functions/main_functions.cpp classes/Bitcoin.cpp classes/Bitcoin.h classes/Lists/BitcoinList.cpp classes/Lists/BitcoinList.h classes/Lists/StringList.cpp classes/Lists/StringList.h classes/Wallet.cpp classes/Wallet.h)