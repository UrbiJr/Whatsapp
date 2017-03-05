
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  {
		char string[250];
} Text ;

char * getTxt(Text *) ;
Text * setTxt(Text * , char * );

#endif
