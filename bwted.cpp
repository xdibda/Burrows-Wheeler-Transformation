/**
 * Author: Lukas Dibdak
 * Subject: KKO
 * Faculty: FIT
 * Year: 2016/2017
 * University: VUT Brno
 */

#include <iostream>
#include <map>

#include "bwted.h"

using namespace std;

int getFileSize(FILE* inputFile) {
    fseek(inputFile, 0L, SEEK_END);
    int size = (int) ftell(inputFile);
    fseek(inputFile, 0L, SEEK_SET);
    return size;
}

void getFileData(FILE* inputFile, deque<char> *result) {
    int character;
    while ((character = fgetc(inputFile)) != EOF) {
        result->push_back((char) character);
    }
}

void getFileData(FILE* inputFile, deque<int64_t> *result) {
    int character;
    while ((character = fgetc(inputFile)) != EOF) {
        result->push_back((int64_t) character);
    }
}

const char* generateStringAsResult(deque<int64_t> source) {
    vector<char> result;
    for (deque<int64_t >::iterator it = source.begin(); it != source.end(); it++) {
        char c = (int) *it;
        cout << "Reading: " << c << endl;
        result.push_back(*it);
    }

    return result.data();
}

const char* generateStringAsResult(deque<char> source) {
    vector<char> result;
    for (deque<char>::iterator it = source.begin(); it != source.end(); it++) {
        result.push_back(*it);
    }

    return result.data();
}

int BWTEncoding(tBWTED *bwted, FILE *inputFile, FILE *outputFile) {
/*    deque<char> fileData;
    getFileData(inputFile, &fileData);
    bwted->uncodedSize = (int64_t) fileData.size();*/

    deque<char> fileData;
    fileData.push_back('t');
    fileData.push_back('s');
    fileData.push_back('e');
    fileData.push_back('s');
    fileData.push_back('s');
    fileData.push_back('s');
    fileData.push_back('t');
    fileData.push_back('e');
    fileData.push_back('e');

    cout << "Vstupní soubor je:" << endl;
    for (deque<char>::iterator it = fileData.begin(); it != fileData.end(); ++it) {
        cout << *it << endl;
    }

    cout << "Konec. Jdu dělat BWT:" << endl;

    BWT *bwt = new BWT();
    vector<char> BWTResult;
    bwt->encode(fileData, &BWTResult);

    cout << "Výsledek BWT:" << endl;
    for (vector<char>::iterator it = BWTResult.begin(); it != BWTResult.end(); ++it) {
        cout << *it << endl;
    }

    cout << "Konec. Jedu dělat MTF:" << endl;

    MTF *mtf = new MTF();
    deque<int64_t > MTFResult;
    mtf->encode(BWTResult, &MTFResult);

    cout << "Výsledek MTF:" << endl;
    for (deque<int64_t>::iterator it = MTFResult.begin(); it != MTFResult.end(); ++it) {
        cout << *it << endl;
    }

    cout << "Konec. Jedu dělat RLE:" << endl;

    RLE *rle = new RLE();
    deque<int64_t> RLEResult;
    rle->encode(MTFResult, &RLEResult);

    cout << "Výsledek RLE:" << endl;
    for (deque<int64_t>::iterator it = RLEResult.begin(); it != RLEResult.end(); ++it) {
        cout << *it << endl;
    }

    cout << "Generated string: " << generateStringAsResult(RLEResult) << endl;

    fprintf(outputFile, "%s", generateStringAsResult(RLEResult));
    bwted->codedSize = getFileSize(outputFile);
    return EXIT_SUCCESS;
}

int BWTDecoding(tBWTED *bwted, FILE *inputFile, FILE *outputFile) {
    bwted->codedSize = getFileSize(inputFile);

    deque<int64_t > fileData;
    getFileData(inputFile, &fileData);

    RLE *rle = new RLE();
    deque<int64_t> RLEResult;
    rle->decode(fileData, &RLEResult);

    MTF *mtf = new MTF();
    vector<char> MTFResult;
    mtf->decode(RLEResult, &MTFResult);

    BWT *bwt = new BWT();
    deque<char> BWTResult;
    bwt->decode(MTFResult, &BWTResult);

    fprintf(outputFile, "%s", generateStringAsResult(BWTResult));
    bwted->uncodedSize = (int64_t) fileData.size();
    return EXIT_SUCCESS;
}