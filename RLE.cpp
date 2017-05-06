//
// Created by Lukáš Dibďák on 03.05.17.
//

#include "RLE.h"

void RLE::encode(deque<int64_t> source, deque<char> *result) {
    char actual;
    int length = 0, counter = 0;
    while (!source.empty()) {
        int64_t character = source.front();
        source.pop_front();

        counter++;

        if (counter == 1) {
            actual = character;
            continue;
        }

        if (actual == character) {
            length++;
        } else {
            if (length < 4) {
                for (int i = 0; i < length; i++) {
                    result->push_back(actual);
                }
            } else {
                result->push_back('@');
                result->push_back(length);
                result->push_back(actual);
            }

            length = 0;
            actual = character;
        }
    }
}

void RLE::decode(deque<int64_t > source, deque<int64_t> *result) {

}