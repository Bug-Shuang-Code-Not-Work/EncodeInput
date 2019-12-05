/*
File: main.c
Project : encodeInput
Programmer : Shuang Liang 7492259
First Version : 2018 - 02 - 23
Description : This program is a linux utility for encrypting information to binary in SREC and Assembly format.
*/
#include "../inc/encodeInput.h"




int main(int argc, char* argv[]) {


	//parse command line to identify command 
	int retCode = parseCommandLine(argc, argv);

	if (retCode == ERROR) {

		printf("Invalid Format! Please use <-h> to look at user manual.\n");

	}

	else if (retCode == HELP) {

		printf("encodeInput <[-i]INPUTFILENAME> <[-o]OUTPUTFILENAME> <-srec> <-h>\n");

	}

	return 0;
}





