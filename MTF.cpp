//
// Created by Lukáš Dibďák on 03.05.17.
//

#include "MTF.h"

void MTF::initSymbolTable(deque<char> *symbolTable) {
    for (int i = 0; i < 127; ++i) {
        symbolTable->push_back((char) i);
    }
}

void MTF::updateSymbolTable(deque<char> *symbolTable, int position) {
    char character = symbolTable->at((unsigned long) position);
    symbolTable->erase(symbolTable->begin() + position);
    symbolTable->push_front(character);
}

void MTF::encode(vector<char> source, deque<char> *result) {
    deque<char> symbolTable;

    initSymbolTable(&symbolTable);

    int symbolTableSize = (int) symbolTable.size();
    for (int i = 0; i < (int) source.size(); ++i) {
        for (int j = 0; j < symbolTableSize; ++j) {
            if (source[i] == symbolTable.at(j)) {
                result->push_back(j + '0');
                updateSymbolTable(&symbolTable, j);
            }
        }
    }
}

void MTF::decode(deque<int64_t> source, vector<char> *result) {

}