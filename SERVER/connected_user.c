
/*!	\file connected_user.c
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#include "connected_user.h"

/*!	\fn set_con_username
	\brief set the username
	\param u connected user
	\param s new username
	\return connected user
*/
recConnectedUser *set_con_username(recConnectedUser *u, char *s){
	memset(u->username, 0, sizeof u->username);
	strcpy(u->username, s);

	return u;
}

/*!	\fn set_socket
	\brief set the socket
	\param u connected user
	\param s new socket
	\return connected user
*/
recConnectedUser *set_socket(recConnectedUser *u, int socket){
	u->socket = socket;
	return u;
}

/*!	\fn get_con_username
	\brief get the username
	\param u connected user
	\return connected user
*/
char *get_con_username(recConnectedUser *u){
	return u->username;
}

/*!	\fn get_socket
	\brief get the socket
	\param u connected user
	\return connected user
*/
int get_socket(recConnectedUser *u){
	return u->socket;
}

/*!	\fn already_connected
 	\brief checks if a user is already connected
    \param u connected user
    \param n current number of connected users
    \param str username
    \return TRUE if already connected, FALSE otherwise
*/
int already_connected(recConnectedUser *u, int n, char *str){
	for(n; n > 0; n--)
		if(strcmp(u[n].username, str) == 0)
			return TRUE;

	return FALSE;
}

/*!	\fn find_connected_user
 	\brief get the index of a connected user
    \param users connected users array
    \param u connected user
    \param n current number of connected users
    \return the index of the connected user on success, -1 otherwise
*/
int find_connected_user(recConnectedUser *users, recConnectedUser u, int n){

	int i;

	for(i = 0; i < n; i++)
		if (strcmp(users[i].username, u.username) == 0 &&
			users[i].socket == u.socket){
			return i;
		}

	return -1;
}

/*!	\fn remove_connected_user
 	\brief removes a connected user from the array
    \param users connected users array
    \param u connected user to remove
    \param n current number of connected users
    \return 0 on success, -1 otherwise
*/
int remove_connected_user(recConnectedUser *users, recConnectedUser u, int *n){
	
	int index = find_connected_user(users, u, *n);
	if(index == -1) return -1;


	if(index != (*n - 1))
		memmove(&users[index], &users[index+1], ((*n-1)-index) * sizeof(users[0]));
	memset(&users[*n-1], 0, sizeof(users[*n-1]));

	(*n)--;

	return 0;
}
