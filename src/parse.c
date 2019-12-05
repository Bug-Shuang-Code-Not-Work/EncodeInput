/*
File: parse.c
Project: encodeInput
Programmer: Shuang Liang 7492259
First Version: 2018-02-23
Description: This file contains functions to handle command line argument and decide which method and actions to be taken
*/

#include "../inc/encodeInput.h"



/*
Function: parseCommandLine
Parameter: int argc, char* argv[] (count of command line argument, array of command line argument)
Return Value: 0 if proper actions are taken and -1 otherwise
Description: This function takes in the input command line arguement and identify the proper actions to be taken.
*/
int parseCommandLine(int argc, char* argv[]) {

	// the have variable help to identify input format if there is only one of each switch
	 int haveInputSwitch = 0;
	 int haveOutputSwitch = 0;
	 int haveSrecSwitch = 0;
	 int haveHelpSwitch = 0;

	//input and output file names are initialized 
	char inputFile[STR_LEN] = "Not Specified";
	char outputFile[STR_LEN] = "Not Specified";

	char buffer[STR_LEN] = "";

	//too many arguments
	if (argc > 5) {

		 return ERROR;

	}

	//no argument is the default encode to assembly from stdin to stdout
	if (argc == 1) {

	  //call assem function 
	 fileStream(inputFile, outputFile, 0);

		  return 0;
	 }


 /*------------------------------------------------------------------------------------------*/
 /*---------------------check content of each individual argument in a loop------------------*/
 /*------------------------------------------------------------------------------------------*/
//the loop is meant to identify every argument and 
for (int i = 1; i < argc; ++i) {


	// copy the argument into buffer to exam
	strcpy(buffer, argv[i]);

	// help argument confirmed and mutiple is allowed
		if (strcmp(buffer, "-h") == 0) {

		haveHelpSwitch++;

		}

		//srec argument comfirmed and mutiple is allowed
		else if (strcmp(buffer, "-srec") == 0) {

		haveSrecSwitch++;

		}

		//input argument comfirmed and only one allowed
		else if (buffer[0] == '-' && buffer[1] == 'i') {

		haveInputSwitch++;

		// if the file name is specified													
			if (buffer[2] != '\0' && haveInputSwitch == 1) {

			char* pCopy = &buffer[2];
			strcpy(inputFile, pCopy);

			}


		}

		//output argument comfirmed and only one allowed
		else if (buffer[0] == '-' && buffer[1] == 'o') {


		haveOutputSwitch++;

			//if the file name is specified 
			if (buffer[2] != '\0' && haveOutputSwitch == 1) {

			char* pCopy = &buffer[2];
			strcpy(outputFile, pCopy);

			}


		}

		//invalid input is in the argument
		else {

		return ERROR;
	
	}



}
	//end of the loop


	/*------------------------------------------------------------------------------------------*/
	 /*--------------------------------determine which mode to call------------------------------*/
	 /*------------------------------------------------------------------------------------------*/


		  // check help switch first and go to manual once identified
		  if (haveHelpSwitch > 0) {

			  return HELP;

		  }

		  // correct input and output format
		  if (haveInputSwitch <= 1 && haveOutputSwitch <= 1) {

			  fileStream(inputFile, outputFile, haveSrecSwitch);
			  return 0;

		  }


		  //mutiple input or output switches are invalid 
		  else {

			  return ERROR;
		  }


}






/*
Function: fileStream
Parameter: char* inputName, char* outputName, int srecSwitch(input file name, output file name, SREC switch)
Return Value: 0 if input arguments are correct and -1 otherwise
Description: This function identifies the file streams, open and close both the input and output file stream
*/
int fileStream(char* inputName, char* outputName, int srecSwitch) {


	  //find out the input and output file stream
	  char noFileName[STR_LEN] = "Not Specified";
	  FILE* inputStream = NULL;
	  FILE* outputStream = NULL;

	  // from stdin to stdout
	  if (strcmp(inputName, noFileName) == 0 && strcmp(outputName, noFileName) == 0) {

		  inputStream = stdin;
		  outputStream = stdout;

		  if (srecSwitch > 0) {


			  srecMode(inputStream, outputStream);
			  
		  }

		  else {

	
			  asemMode(inputStream, outputStream);
			 
		  }

	  }


	  //from stdin to output file
	  if (strcmp(inputName, noFileName) == 0 && strcmp(outputName, noFileName) != 0) {

		  inputStream = stdin;
		  outputStream = fopen(outputName, "wb");

		  if (outputStream == NULL) {


			  return ERROR;

		  }

		  if (srecSwitch > 0) {

			  srecMode(inputStream, outputStream);

		  }
		  else {


			  asemMode(inputStream, outputStream);

		  }

	  }


	  //from input file to same name output file with .asm extension
	  if (strcmp(inputName, noFileName) != 0 && strcmp(outputName, noFileName) == 0) {

		  char asmExtension[STR_LEN] = ".asm";
		  char srecExtension[STR_LEN] = ".srec";
		  char outputFile[STR_LEN] = "";

		  inputStream = fopen(inputName, "rb");

		  if (inputStream == NULL) {

			  printf("Failed to open the input file!\n");
			  return ERROR;

		  }

		  strcpy(outputFile, inputName);

		  if (srecSwitch > 0) {

			  strcat(outputFile, srecExtension);
			  outputStream = fopen(outputFile, "wb");
			  if (outputStream == NULL) {

				  printf("Failed to open the output file!\n");
				  return ERROR;
			  }

			  srecMode(inputStream, outputStream);
			  
		  }

		  else {

			  strcat(outputFile, asmExtension);
			  outputStream = fopen(outputFile, "wb");
			  if (outputStream == NULL) {

				  printf("Failed to open the output file!\n");
				  return ERROR;
			  }

			  asemMode(inputStream, outputStream);
			 
		  }


	  }

	  //from input file to output file
	  if (strcmp(inputName, noFileName) != 0 && strcmp(outputName, noFileName) != 0) {


		  inputStream = fopen(inputName, "rb");
		  if (inputStream == NULL) {

			  printf("Failed to open the input file!\n");
			  return ERROR;
		  }

		  outputStream = fopen(outputName, "wb");
		  if (outputStream == NULL) {

			  printf("Failed to open the output file!\n");
			  return ERROR;
		  }

		  if (srecSwitch > 0) {

			  srecMode(inputStream, outputStream);
		  }

		  else {

			  asemMode(inputStream, outputStream);
		  }


	  }



	if (fclose(inputStream) != 0) {


		 printf("Failed to close the input file!\n");
		 return ERROR;
	}

	 if (fclose(outputStream) != 0) {

	  printf("Failed to close the output file!\n");
	  return ERROR;

	 }

  return 0;

 }


