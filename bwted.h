/**
 * Author: Lukas Dibdak
 * Subject: KKO
 * Faculty: FIT
 * Year: 2016/2017
 * University: VUT Brno
 */

#ifndef KKO_BWTED_H
#define KKO_BWTED_H

#include "MTF.h"
#include "BWT.h"
#include "RLE.h"

using namespace std;

/**
 * compress record
 */
typedef struct {
    int64_t uncodedSize;
    int64_t codedSize;
} tBWTED;

/**
 * bwted: compress record
 * @return: 0 success/ 1 failed
 */
int BWTEncoding(tBWTED *bwted, FILE *inputFile, FILE *outputFile);

/**
 * bwted: compress record
 * @return: 0 success/ 1 failed
 */
int BWTDecoding(tBWTED *bwted, FILE *inputFile, FILE *outputFile);

void getFileData(FILE* inputFile, deque<int64_t> *result);
void getFileData(FILE* inputFile, deque<char> *result);

int getFileSize(FILE* inputFile);

const char* generateStringAsResult(deque<char> source);
const char* generateStringAsResult(deque<int64_t> source);

#endif
