
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef CONNECTEDUSER_H
#define CONNECTEDUSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

typedef struct{
	char username[20];
	int sock;
}recConnectedUser;

recConnectedUser *setConnectedUsername(recConnectedUser * , char * );
recConnectedUser *setSock(recConnectedUser * , int );
char *getConnectedUsername(recConnectedUser * );
int getSock(recConnectedUser * );
int alreadyConnected(recConnectedUser * , int , char *);
int findConnectedUser(recConnectedUser * , recConnectedUser , int );
int removeConnectedUserFromArray(recConnectedUser * , recConnectedUser , int * );

#endif
