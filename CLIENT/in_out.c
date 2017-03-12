
/*!	\file in_out.c
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#include "in_out.h"

/*!	
	\brief open a file
	\param file_name filename
	\param mode 'w','r','a',"wb","rb"
	\return file pointer
*/
FILE *open_file(char *file_name, char *mode){

	FILE *fp;

	fp = fopen(file_name, mode);
	if(!fp)
		perror("File opening error:");

	return fp;
}

/*!	
	\brief close a file
	\param fp file pointer
*/	
void close_file(FILE *fp){
	fclose(fp);
}

/*!	
	\brief write data to a file
	\param fp file pointer
	\param buf data
	\param data_size data size
*/
void write_to_file(FILE *fp, char *buf, int data_size){

	int i;
	
	for(i = 0; i < data_size; i++)
		putc(buf[i], fp);
}

/*!	
	\brief write message (recMessage) to a file
	\param fp file pointer
	\param m message
*/
void write_message_to_file(FILE *fp, recMessage *m){

	fwrite(m, sizeof (recMessage), 1, fp);
}	

/*! 
	\brief read a message (recMessage) from a file
	\param fp file pointer
	\return message
*/
recMessage read_message_from_file(FILE *fp){

	recMessage m;

	fread(&m, sizeof (recMessage), 1, fp);

	return m;
}

/*!	
	\brief copy a file content into another
	\param fpin file pointer input
	\param fpout file pointer output
*/
void copy_file(FILE *fpin, FILE *fpout){

	int c;

	while((c = getc(fpin)) != EOF) putc(c, fpout);
}
