//
// Created by Lukáš Dibďák on 03.05.17.
//

#ifndef KKO_MTF_H
#define KKO_MTF_H

#include <deque>
#include <vector>

using namespace std;

class MTF {
public:
    void initSymbolTable(deque<char> *symbolTable);
    void updateSymbolTable(deque<char> *symbolTable, int position);

    void encode(vector<char> source, deque<int64_t> *result);
    void decode(deque<int64_t> source, vector<char> *result);
};


#endif //KKO_MTF_H
