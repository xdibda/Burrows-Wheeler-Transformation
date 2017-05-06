//
// Created by Lukáš Dibďák on 03.05.17.
//

#ifndef KKO_RLE_H
#define KKO_RLE_H

#include <deque>
#include <stdlib.h>

using namespace std;

class RLE {
public:
    void encode(deque<int64_t> source, deque<int64_t > *result);
    void decode(deque<int64_t > source, deque<int64_t> *result);
};


#endif //KKO_RLE_H
