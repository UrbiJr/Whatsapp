/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef INOUT_H
#define INOUT_H

#include <stdio.h>
#include <stdlib.h>

#include "message.h"

FILE *openFile(char * , char * );
int closeFile(FILE * );
void writeToFile(FILE * , char * , int );
void writeMessageToFile(FILE * , recMessage * ); 
recMessage readMessageFromFile(FILE *pf);
void copyFile(FILE * , FILE * );

#endif
