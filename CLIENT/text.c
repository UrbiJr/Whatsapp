
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "text.h"

char * getTxt(Text * t) {
		return(t->string);
}

Text * setTxt(Text * t, char * strt) {
		strcpy(t -> string, strt);
      return(t);
}
