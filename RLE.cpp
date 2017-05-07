//
// Created by Lukáš Dibďák on 03.05.17.
//

#include "RLE.h"
#include <string>
#include <sstream>
#include <iostream>

void RLE::encode(deque<int> source, deque<string> *result) {
    deque<int> pairs[2];

    int actual = 0, length = 0, counter = 0;
    while (!source.empty()) {
        int character = source.front();
        source.pop_front();

        counter++;
        if (counter == 1) {
            actual = character;
            length++;
            continue;
        }

        if (actual == character) {
            length++;
        } else {
            pairs[0].push_back(length);
            pairs[1].push_back(actual);

            actual = character;
            length = 1;
        }
    }

    if (counter != 0) {
        pairs[0].push_back(length);
        pairs[1].push_back(actual);
    }

    while (!pairs[0].empty() && !pairs[1].empty()) {
        int number = pairs[0].front();
        pairs[0].pop_front();
        int character = pairs[1].front();
        pairs[1].pop_front();

        if (number < 4) {
            for (int i = 0; i < number; ++i) {
                stringstream ss;
                ss << character;
                string ssstr = ss.str();

                result->push_back(ssstr);
            }
        } else {
            stringstream ss;
            ss << '@';
            string ssstr = ss.str();

            stringstream ssnumber;
            ssnumber << number;
            string ssnumberstr = ssnumber.str();

            stringstream sschar;
            sschar << character;
            string sscharstr = sschar.str();

            result->push_back(ssstr);
            result->push_back(ssnumberstr);
            result->push_back(sscharstr);
        }
    }
}

void RLE::decode(deque<char> source, deque<int> *result) {
    char character; string actual;

    while (!source.empty()) {
        character = source.front();
        source.pop_front();

        if (character == ' ') {
            result->push_back(atoi(actual.c_str()));
            actual.clear();
        } else if (character == '@') {
            string number, length;

            character = source.front();
            source.pop_front();

            while (!source.empty()) {
                character = source.front();
                source.pop_front();

                if (character != ' ') {
                    length += character;
                }  else {
                    break;
                }
            }

            while (!source.empty()) {
                character = source.front();
                source.pop_front();

                if (character != ' ') {
                    number += character;
                }  else {
                    break;
                }
            }

            for (int i = 0; i < atoi(length.c_str()); i++) {
                result->push_back(atoi(number.c_str()));
            }
        } else {
            actual += character;
        }
    }
}