
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "user.h"

recUser *setUsername(recUser *a, char *s){
	memset(a->username, 0, sizeof a->username);
	strcpy(a->username, s);

	return a;
}

recUser *setPassword(recUser *a, char *s){
	memset(a->password, 0, sizeof a->password);
	strcpy(a->password, s);

	return a;
}

recUser *setName(recUser *a, char *s){
	memset(a->name, 0, sizeof a->name);
	strcpy(a->name, s);

	return a;
}

recUser *setSurname(recUser *a, char *s){
	memset(a->surname, 0, sizeof a->surname);
	strcpy(a->surname, s);

	return a;
}

char *getUsername(recUser *a){
	return a->username;
}

char *getPassword(recUser *a){
	return a->password;
}

char *getName(recUser *a){
	return a->name;
}

char *getSurname(recUser *a){
	return a->surname;
}

/**
 * writes users array into file
 * @param  pf file in which store the users
 * @param  a  recUser array
 * @return    number of users (array elements)
 */
int storeUsers(FILE *pf, recUser *a){

	int iUsers = 0;

	rewind(pf);
	memset(a, 0, sizeof(a));
	while(fscanf(pf, "%s %s %s %s\n", a[iUsers].username, a[iUsers].password, a[iUsers].name, a[iUsers].surname) == 4){
		iUsers++;
	}

	rewind(pf);

	return iUsers;
}

/**
 * looks for a username inside the indexbook
 * @param  pf indexbook file pointer
 * @param  s1 username
 * @return    TRUE on success, FALSE otherwise
 */
int findUsername(FILE *pf, char *username){

	char s[25];
	char line[250];
	int f = FALSE;

	do{
		// read until " "
		fscanf(pf,"%[^ ]", s);
		if(strcmp(username, s) == 0)
			f = TRUE;
		else
			// move to the end of line
			fgets(line, 250, pf);
	}while(!feof(pf) && f == 0);

	return f;
}
