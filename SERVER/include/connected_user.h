
/*!	\file connected_user.h
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0
	\date 06/03/2017
*/

#ifndef CONNECTEDUSER_H
#define CONNECTEDUSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

typedef struct{
	char username[20];
	int socket;
}recConnectedUser;

recConnectedUser *set_con_username(recConnectedUser * , char * );
recConnectedUser *set_socket(recConnectedUser * , int );
char *get_con_username(recConnectedUser * );
int get_socket(recConnectedUser * );
int already_connected(recConnectedUser * , int , char *);
int find_connected_user(recConnectedUser * , recConnectedUser , int );
int remove_connected_user(recConnectedUser * , recConnectedUser , int * );

#endif
