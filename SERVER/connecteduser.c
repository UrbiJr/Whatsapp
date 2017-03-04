
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "connecteduser.h"

recConnectedUser *setConnectedUsername(recConnectedUser *a, char *s){
	memset(a->username, 0, sizeof a->username);
	strcpy(a->username, s);

	return a;
}

recConnectedUser *setSock(recConnectedUser *a, int sock){
	a->sock = sock;
	return a;
}

char *getConnectedUsername(recConnectedUser *a){
	return a->username;
}

int getSock(recConnectedUser *a){
	return a->sock;
}

/**
 * check if a user is already connected
 * @param  a   user
 * @param  n   current number of connected users
 * @param  str username
 * @return     TRUE if already connected, FALSE otherwise
 */
int alreadyConnected(recConnectedUser *a, int n, char *str){
	for(n; n > 0; n--)
		if(strcmp(a[n].username, str) == 0)
			return TRUE;

	return FALSE;
}

/**
 * get the index of a connected user
 * @param  users array
 * @param  u     user
 * @param  n     current number of connected users
 * @return       the index of the connected user on success, -1 otherwise
 */
int findConnectedUser(recConnectedUser *users, recConnectedUser u, int n){

	int i;

	for(i = 0; i < n; i++)
		if (strcmp(users[i].username, u.username) == 0 &&
			users[i].sock == u.sock){
			return i;
		}

	return -1;
}

/**
 * remove a connecteduser struct from the array
 * @param  users array
 * @param  u     user to remove
 * @param  n     current number of connected users
 * @return       0 on success, -1 otherwise
 */
int removeConnectedUserFromArray(recConnectedUser *users, recConnectedUser u, int *n){
	
	int index = findConnectedUser(users, u, *n);
	if(index == -1) return -1;


	if(index != (*n - 1))
		memmove(&users[index], &users[index+1], ((*n-1)-index) * sizeof(users[0]));
	memset(&users[*n-1], 0, sizeof(users[*n-1]));

	(*n)--;

	return 0;
}
