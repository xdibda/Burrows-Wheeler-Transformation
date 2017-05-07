/**
 * Author: Lukas Dibdak
 * Subject: KKO
 * Faculty: FIT
 * Year: 2016/2017
 * University: VUT Brno
 */

#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
#include <iostream>

#include "bwted.h"

/**
 * Error messages
 */
const char* ERROR_BAD_ARG = "Bad arguments.\n";
const char* ERROR_TWO_TASK = "Both -x and -c set, choose only one.\n";
const char* ERROR_NO_TASK = "No task selected. Choose either -c or -x.\n";
const char* ERROR_OPEN_FILE = "One of the file you have set could not be opened.\n";

/**
 * Compress (-c) or decompress tasks (-x)
 */
const int TASK_NONE = 0;
const int TASK_COMPRESS = 1;
const int TASK_DECOMPRESS = 2;

const int CONTROL_CONTINUE = 3;
const int CONTROL_HELP = 4;
const int CONTROL_TWO_TASKS = 5;
const int CONTROL_NO_TASK = 6;
const int CONTROL_BAD_ARG = 7;

static int counter = 0;

/**
 * Argument structure
 */
struct Arguments {
    int type;

    bool inputSet;
    bool outputSet;
    bool logSet;

    const char *inputFile;
    const char *outputFile;
    const char *logFile;
} arguments = {TASK_NONE, false, false, false, "none", "none", "none"};

/**
 * Functions declaration, specification of each function at its description
 */
int controlArguments(int argc, char *argv[], struct Arguments *arguments);

void help();
void openFiles(FILE **input, FILE **output, FILE **log);
void closeFiles(FILE **input, FILE **output, FILE **log);

void compressFile(FILE* input, FILE* output, FILE* log);
void decompressFile(FILE* input, FILE* output, FILE* log);

bool filesOpenedCorrectly();

FILE *openFile(const char *fileName, const char *fileArguments);

/**
 * Main function
 */
int main(int argc, char *argv[]) {
    switch (controlArguments(argc, argv, &arguments)) {
        case CONTROL_HELP:
            help();
            return EXIT_SUCCESS;

        case CONTROL_TWO_TASKS:
            fprintf(stderr, "%s", ERROR_TWO_TASK);
            return EXIT_FAILURE;

        case CONTROL_NO_TASK:
            fprintf(stderr, "%s", ERROR_NO_TASK);
            return EXIT_FAILURE;

        case CONTROL_BAD_ARG:
            fprintf(stderr, "%s", ERROR_BAD_ARG);
            return EXIT_FAILURE;

        case CONTROL_CONTINUE:
        default:
            break;

    }

    FILE *input, *output, *log;
    openFiles(&input, &output, &log);

    if (!filesOpenedCorrectly()) {
        fprintf(stderr, "%s", ERROR_OPEN_FILE);
        return EXIT_FAILURE;
    }

    switch (arguments.type) {
        case TASK_COMPRESS:
            compressFile(input, output, log);
            break;

        case TASK_DECOMPRESS:
            decompressFile(input, output, log);
            break;

        default:
            break;
    }

    closeFiles(&input, &output, &log);
    return EXIT_SUCCESS;
}

/**
 * Function that prints output message in desired format
 */
void printResults(tBWTED bwted, FILE* log) {
    fprintf(log, "login = %s\n", "xdibda00");
    fprintf(log, "uncodedSize = %d\n", bwted.uncodedSize);
    fprintf(log, "codedSize = %d\n", bwted.codedSize);
}

/**
 * Compress function
 */
void compressFile(FILE* input, FILE* output, FILE* log) {
    tBWTED bwted;

    if (BWTEncoding(&bwted, input, output) != 1 && arguments.logSet) {
        printResults(bwted, log);
    }
}

/**
 * Decompress function
 */
void decompressFile(FILE* input, FILE* output, FILE* log) {
    tBWTED bwted;
    if (BWTDecoding(&bwted, input, output) != 1 && arguments.logSet) {
        printResults(bwted, log);
    }
}

/**
 * Opening files and setting streams
 */
void openFiles(FILE **input, FILE **output, FILE **log) {
    *input = arguments.inputSet ? openFile(arguments.inputFile, "rb") : stdin;
    *output = arguments.outputSet ? openFile(arguments.outputFile, "wb") : stdout;
    *log = arguments.logSet ? openFile(arguments.logFile, "wb") : NULL;
}

FILE *openFile(const char *fileName, const char *fileArguments) {
    FILE *file = fopen(fileName, fileArguments);

    if (!file) {
        counter++;
        return NULL;
    }

    return file;
}

/**
 * File fail opening counter
 */
bool filesOpenedCorrectly() {
    return counter == 0;
}

/**
 * Closing files
 */
void closeFiles(FILE **input, FILE **output, FILE **log) {
    if (arguments.inputSet) {
        fclose(*input);
    }

    if (arguments.outputSet) {
        fclose(*output);
    }

    if (arguments.logSet) {
        fclose(*log);
    }
}

/**
 * Help function
 */
void help() {
    printf("------------------------------------------------------------------------------");
    printf("Input arguments:");
    printf("1) -c => compress.");
    printf("2) -x => decompress.");
    printf("3) -i <inputFile> => input file, if not set, input source is stdin.");
    printf("4) -o <outputFile> => output file, if not set, output source is stdout.");
    printf("5) -l <logFile> => output message file, if not set, output message is ignored.");
    printf("------------------------------------------------------------------------------");
}

/**
 * Arguments control function
 */
int controlArguments(int argc, char *argv[], struct Arguments *arguments) {
    const char *acceptedArguments = "i:o:l:hcx";

    int arg;
    while ((arg = getopt(argc, argv, acceptedArguments)) != -1) {
        switch (arg) {
            case 'h':
                return CONTROL_HELP;

            case 'c':
                if (arguments->type == TASK_DECOMPRESS) {
                    return CONTROL_TWO_TASKS;
                } else {
                    arguments->type = TASK_COMPRESS;
                }
                break;

            case 'i':
                arguments->inputSet = true;
                arguments->inputFile = optarg;
                break;

            case 'o':
                arguments->outputSet = true;
                arguments->outputFile = optarg;
                break;

            case 'l':
                arguments->logSet = true;
                arguments->logFile = optarg;
                break;

            case 'x':
                if (arguments->type == TASK_COMPRESS) {
                    return CONTROL_TWO_TASKS;
                } else {
                    arguments->type = TASK_DECOMPRESS;
                }
                break;

            default:
                return CONTROL_BAD_ARG;
        }
    }

    if (arguments->type == TASK_NONE) {
        return CONTROL_NO_TASK;
    }

    return CONTROL_CONTINUE;
}