//
// Created by Lukáš Dibďák on 03.05.17.
//

#ifndef KKO_BWT_H
#define KKO_BWT_H

#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

class BWT {
public:
    void encode(deque<char> source, vector<char> *result);
    void decode(string source, string *result);

    vector<char> getResultFromPermutation(vector<deque<char>> files);
    deque<char> makeShift(deque<char> *file);

    vector<deque<char>> createPermutations(deque<char> file);
};


#endif //KKO_BWT_H
