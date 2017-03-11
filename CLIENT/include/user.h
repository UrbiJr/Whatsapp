
/*!	\file user.h
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

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

recUser *set_username(recUser * , char * );
recUser *set_password(recUser * , char * );
recUser *set_name(recUser * , char * );
recUser *set_surname(recUser * , char * );
char *get_username(recUser * );
char *get_password(recUser * );
char *get_name(recUser * );
char *get_surname(recUser * );
int find_username(FILE * , char * );
int store_users(FILE * , recUser * );

#endif
