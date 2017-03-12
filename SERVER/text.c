
/*!	\file text.c
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#include "text.h"


/*	
	\brief set the string of a text
	\param t text
	\param str new string
	\return text (t)
*/
recText * set_string(recText *t, char *str){
	strcpy(t->string, str);

    return t;
}

/*! 
	\brief get the string of a text
	\param t text
	\return string of the text
*/
char * get_string(recText *t){
	return t->string;
}
