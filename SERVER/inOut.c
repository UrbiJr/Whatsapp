
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "inOut.h"

FILE *openFile(char *fileName, char *mode){

	FILE *pf;

	pf = fopen(fileName, mode);
	if(!pf)
		perror("File opening error:");

	return pf;
}

int closeFile(FILE *pf){

	if(pf){
		fclose(pf);
		return 1;
	}

	return 0;
}

void writeToFile(FILE *pf, char *buf, int data_size){

	int i;
	
	for(i = 0; i < data_size; i++)
		putc(buf[i], pf);
}

void writeMessageToFile(FILE *pf, recMessage *m){

	fwrite(m, sizeof (recMessage), 1, pf);
}	
	
recMessage readMessageFromFile(FILE *pf){

	recMessage m;

	fread(&m, sizeof (recMessage), 1, pf);

	return m;
}

void copyFile(FILE *pfin, FILE *pfout){

	int c;

	while((c = getc(pfin)) != EOF) putc(c, pfout);
}
