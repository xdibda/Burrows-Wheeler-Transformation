//
// Created by Lukáš Dibďák on 03.05.17.
//

#ifndef KKO_RLE_H
#define KKO_RLE_H

#include <deque>
#include <stdlib.h>
#include <string>

using namespace std;

class RLE {
public:
    void encode(deque<int> source, deque<string> *result);
    void decode(deque<char> source, deque<int> *result);
};


#endif //KKO_RLE_H
