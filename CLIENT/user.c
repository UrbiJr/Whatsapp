
/*!	\file user.c
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#include "user.h"

/*!	\fn set_username
	\brief set the username of a user
	\param u user
	\param s new username
	\return user (u)
*/
recUser *set_username(recUser *u, char *s){
	memset(u->username, 0, sizeof u->username);
	strcpy(u->username, s);

	return u;
}

/*!	\fn set_password
	\brief set the password of a user
	\param u user
	\param s new password
	\return user (u)
*/
recUser *set_password(recUser *u, char *s){
	memset(u->password, 0, sizeof u->password);
	strcpy(u->password, s);

	return u;
}

/*!	\fn set_name
	\brief set the name of a user
	\param u user
	\param s new name
	\return user (u)
*/
recUser *set_name(recUser *u, char *s){
	memset(u->name, 0, sizeof u->name);
	strcpy(u->name, s);

	return u;
}

/*!	\fn set_surname
	\brief set the surname of a user
	\param u user
	\param s new surname
	\return user (u)
*/
recUser *set_surname(recUser *u, char *s){
	memset(u->surname, 0, sizeof u->surname);
	strcpy(u->surname, s);

	return u;
}

/*! \fn get_username
	\brief get the username of a user
	\param u user
	\return username of the user
*/
char *get_username(recUser *u){
	return u->username;
}

/*! \fn get_password
	\brief get the password of a user
	\param u user
	\return password of the user
*/
char *get_password(recUser *u){
	return u->password;
}

/*! \fn get_name
	\brief get the name of a user
	\param u user
	\return name of the user
*/
char *get_name(recUser *u){
	return u->name;
}

/*! \fn get_surname
	\brief get the surname of a user
	\param u user
	\return surname of the user
*/
char *get_surname(recUser *u){
	return u->surname;
}

/*! \fn store_users
	\brief writes users array into file
	\param pf file in which store the users
	\param u recUser array
	\return number of users (array elements)
*/
int store_users(FILE *pf, recUser *u){

	int i_users = 0;

	rewind(pf);
	memset(u, 0, sizeof(u));
	while(fscanf(pf, "%s %s %s %s\n", u[i_users].username, u[i_users].password, u[i_users].name, u[i_users].surname) == 4){
		i_users++;
	}

	rewind(pf);

	return i_users;
}

/*!
	\fn find_username
  	\brief looks for u username inside the indexbook
    \param  pf indexbook file pointer
    \param  s1 username
    \return TRUE on success, FALSE otherwise
 */
int find_username(FILE *pf, char *username){

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
