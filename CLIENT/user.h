
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

typedef struct{
	char username[25];
	char password[25];
	char name[25];
	char surname[25];
}recUser;


recUser *setUsername(recUser * , char * );
recUser *setPassword(recUser * , char * );
recUser *setName(recUser * , char * );
recUser *setSurname(recUser * , char * );
char *getUsername(recUser * );
char *getPassword(recUser * );
char *getName(recUser * );
char *getSurname(recUser * );
int findUsername(FILE * , char * );
int storeUsers(FILE * , recUser * );
#endif
