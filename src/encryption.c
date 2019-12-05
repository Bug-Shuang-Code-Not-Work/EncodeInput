/*
File: encryption.c
Project: encodeInput
Programmer: Shuang Liang 7492259
First Version: 2018-02-23
Description: This files contains all function dealing with encoding input and output for SREC and ASSEMBLY format.
*/

#include "../inc/encodeInput.h"


/*
Function: srecMode
Parameter: FILE* readStream, FILE* writeStream(input and output file handle)
Return Value: 0 
Description: This function takes the input and output file stream and write the encode the input in SREC format
to be written in output file stream
*/
int srecMode(FILE* readStream, FILE* writeStream) {

	//necessary data
	char myName[7] = "SHUANG";
	//4 type record name
	char type[4][3] = {

		"S0", "S1", "S5", "S9"
	};

	char buffer[LINE_SIZE + sizeof(char)] = "";
	int readByte = 0;

	int S0Flag = 0;
	int S1Flag = 0;

	int AAAAS1 = 0;

	//Take the input from the file stream
	while (readByte = fread(buffer, BYTE_SIZE, LINE_SIZE, readStream)) {


		//write S0 line	
		if (S0Flag == 0) {

			int CCS0 = ADDRESS_SIZE + strlen(myName) + BYTE_SIZE;
			int AAAAS0 = 0;

			//TT CC AAAA
			fprintf(writeStream, "%s%02X%04X", type[0], CCS0, AAAAS0);

			int sumDataField = 0;
			for (int i = 0; i < strlen(myName); i++) {

				//DD..DD
				fprintf(writeStream, "%02X", myName[i]);
				sumDataField += myName[i];

			}

			int MM = checkSUM(CCS0, AAAAS0, sumDataField);

			//MM 
			fprintf(writeStream, "%02X\n", MM);

			S0Flag++;
		}

		//write S1 lines

			int CCS1 = ADDRESS_SIZE + readByte + BYTE_SIZE;
			
			int sumData = 0;

			//TT CC AAAA
			fprintf(writeStream, "%s%02X%04X", type[1], CCS1, AAAAS1);

			for (int i = 0; i < readByte; i++) {

				//DD..DD
				fprintf(writeStream, "%02X", buffer[i]);

				sumData += buffer[i];

			}

			//MM
			int MMS1 = checkSUM(CCS1, AAAAS1, sumData);
			fprintf(writeStream, "%02X\n", MMS1);
	
			AAAAS1 += LINE_SIZE;
			S1Flag++;

	}

		if (S0Flag > 0) {

			//write s5 line

			int CCS5 = ADDRESS_SIZE + 0 + BYTE_SIZE;
			int AAAAS5 = S1Flag;
			//TT CC AAAA
			fprintf(writeStream, "%s%02X%04X", type[2], CCS5, AAAAS5);
			int MMS5 = checkSUM(CCS5, AAAAS5, 0);
			//MM
			fprintf(writeStream, "%02X\n", MMS5);



			//write s9 line
			int CCS9 = ADDRESS_SIZE + 0 + BYTE_SIZE;
			int AAAAS9 = 0;
			//TT CC AAAA
			fprintf(writeStream, "%s%02X%04X", type[3], CCS9, AAAAS9);
			int MMS9 = checkSUM(CCS9, AAAAS9, 0);
			//MM
			fprintf(writeStream, "%02X\n", MMS9);



		}


		return 0;

	

}

/*
Function: checkSUM
Parameter: int count, int address, int sumDataField(CC, AAAA, MM)
Return Value: retValue
Description: This funcion calculates the CheckSUM field for the SREC format encoding
*/
int checkSUM(int count, int address, int sumDataField) {

	int retValue = count + address + sumDataField;

	//the 1 's comlement and strip off the LSB

	retValue = (~retValue) & 0xFF;

	return retValue;
}





/*
Function: asemMode
Parameter: FILE* readStream, FILE* writeStream(input and output file handles)
Return Value: 0 
Description: This function takes the input and output file stream and write the encode the input in Assembly format
to be written in output file stream
*/
int asemMode(FILE* readStream, FILE* writeStream) {


	char buffer[LINE_SIZE + sizeof(char)] = "";

	//check if end of file and read bytes
	int readByte = 0;
	while (readByte = fread(buffer, BYTE_SIZE, LINE_SIZE, readStream)) {




		char constantByte[5] = "dc.b";
		fprintf(writeStream, "%s\t\t", constantByte);


		for (int i = 0; i < readByte; i++) {

			if (i == readByte - 1) {

				fprintf(writeStream, "$%02X\n", buffer[i]);

			}

			else {

				fprintf(writeStream, "$%02X,", buffer[i]);

			}
		}

	}
	
	return 0;

}




