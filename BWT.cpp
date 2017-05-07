//
// Created by Lukáš Dibďák on 03.05.17.
//

#include <iostream>
#include "BWT.h"

void BWT::encode(deque<char> source, vector<char> *result) {
    vector<deque<char>> permutations = createPermutations(source);
    *result = getResultFromPermutation(permutations);
}

void BWT::decode(string source, string *result) {
    deque<string> permutations;

    deque<char> original;
    for (int i = 0; i < (int) source.size(); i++) {
        string str;
        original.push_back(source[i]);
        permutations.push_back(str);
    }

    for (int j = 0; j < (int) source.size(); ++j) {
        for (int i = 0; i < (int) source.size(); ++i) {
            string hm = permutations[i];
            string final;
            final += original[i] + hm;
            permutations[i] = final;
        }
        sort(permutations.begin(), permutations.end());
    }

    for (int i = 0; i < (int) permutations.size(); i++) {
        if (permutations[i].back() == '|') {
            *result = permutations[i];
        }
    }
}

vector<char> BWT::getResultFromPermutation(vector<deque<char>> files) {
    vector<char> result;

    for (unsigned long i = 0; i < files.size(); ++i) {
        char last = files.at(i).back();
        result.push_back(last);
    }

    return result;
}

deque<char> BWT::makeShift(deque<char> *file) {
    char character = file->front();
    file->pop_front();
    file->push_back(character);

    return *file;
}

vector<deque<char>> BWT::createPermutations(deque<char> file) {
    vector<deque<char>> permutations;

    for (int i = 0; i < (int) file.size(); i++) {
        permutations.push_back(file);
        file = makeShift(&file);
    }

    sort(permutations.begin(), permutations.end());

    return permutations;
}