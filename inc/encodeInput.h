/*
File: encodeInput.h
Project: encodeInput
Programmer: Shuang Liang 7492259
First Version: 2018-02-23
Description: This header contains all constants and prototypes
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//constants
#define ERROR -1
#define STR_LEN 41
#define SREC 1
#define HELP 3
#define ADDRESS_SIZE 2
#define BYTE_SIZE 1
#define LINE_SIZE 16


//prototypes
int parseCommandLine(int argc, char* argv[]);
int fileStream(char* inputName, char* outputName, int srecSwitch);
int srecMode(FILE* readStream, FILE* writeStream);
int checkSUM(int count, int address, int sumDataField);
int asemMode(FILE* readStream, FILE* writeStream);
