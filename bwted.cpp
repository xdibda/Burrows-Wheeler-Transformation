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

bool isGoodCharacter(int character) {
    return (character != EOF && character != '\n');
}

void getFileData(FILE* inputFile, deque<char> *result) {
    int character;
    while (isGoodCharacter((character = fgetc(inputFile)))) {
        result->push_back((char) character);
    }
}

void getFileData(FILE* inputFile, deque<int64_t> *result) {
    int character;
    while ((character = fgetc(inputFile)) != EOF) {
        result->push_back((int64_t) character);
    }
}

string generateStringAsResult(deque<string> source) {
    string result;
    for (deque<string>::iterator it = source.begin(); it != source.end(); it++) {
        result += *it;
        result += " ";
    }

    return result;
}

int BWTEncoding(tBWTED *bwted, FILE *inputFile, FILE *outputFile) {
    deque<char> fileData;
    getFileData(inputFile, &fileData);
    bwted->uncodedSize = (int) fileData.size();

    BWT *bwt = new BWT();
    vector<char> BWTResult;
    bwt->encode(fileData, &BWTResult);

    MTF *mtf = new MTF();
    deque<int> MTFResult;
    mtf->encode(BWTResult, &MTFResult);

    RLE *rle = new RLE();
    deque<string> RLEResult;
    rle->encode(MTFResult, &RLEResult);

    fprintf(outputFile, "%s\n", generateStringAsResult(RLEResult).c_str());
    bwted->codedSize = getFileSize(outputFile);
    return EXIT_SUCCESS;
}

int BWTDecoding(tBWTED *bwted, FILE *inputFile, FILE *outputFile) {
    deque<char> fileData;
    getFileData(inputFile, &fileData);
    bwted->codedSize = (int) fileData.size();

    RLE *rle = new RLE();
    deque<int> RLEResult;
    rle->decode(fileData, &RLEResult);

    MTF *mtf = new MTF();
    string MTFResult;
    mtf->decode(RLEResult, &MTFResult);

    BWT *bwt = new BWT();
    string BWTResult;
    bwt->decode(MTFResult, &BWTResult);

    fprintf(outputFile, "%s\n", BWTResult.c_str());
    bwted->uncodedSize = (int) BWTResult.size();
    return EXIT_SUCCESS;
}