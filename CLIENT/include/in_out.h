
/*!	\file date.h
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0
	\date 06/03/2017
*/

#ifndef INOUT_H
#define INOUT_H

#include <stdio.h>
#include <stdlib.h>

#include "message.h"

FILE *open_file(char * , char * );
void close_file(FILE * );
void write_to_file(FILE * , char * , int );
void write_message_to_file(FILE * , recMessage * ); 
recMessage read_message_from_file(FILE *pf);
void copy_file(FILE * , FILE * );

#endif
