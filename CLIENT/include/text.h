
/*!	\file text.h
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char string[250];
}recText;

char *get_string(recText * ) ;
recText *set_string(recText * , char * );

#endif
