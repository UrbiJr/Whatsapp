
/*!	\file user.c
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#include "user.h"

/*!	
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

/*!	
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

/*!	
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

/*!	
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

/*! 
	\brief get the username of a user
	\param u user
	\return username of the user
*/
char *get_username(recUser *u){
	return u->username;
}

/*! 
	\brief get the password of a user
	\param u user
	\return password of the user
*/
char *get_password(recUser *u){
	return u->password;
}

/*! 
	\brief get the name of a user
	\param u user
	\return name of the user
*/
char *get_name(recUser *u){
	return u->name;
}

/*! 
	\brief get the surname of a user
	\param u user
	\return surname of the user
*/
char *get_surname(recUser *u){
	return u->surname;
}

/*! 
	\brief writes users array into file
	\param fp file in which store the users
	\param u recUser array
	\return number of users (array elements)
*/
int store_users(FILE *fp, recUser *u){

	int i_users = 0;

	rewind(fp);
	memset(u, 0, sizeof(u));
	while(fscanf(fp, "%s %s %s %s\n", u[i_users].username, u[i_users].password, u[i_users].name, u[i_users].surname) == 4){
		i_users++;
	}

	rewind(fp);

	return i_users;
}

/*!
  	\brief looks for u username inside the indexbook
    \param  fp indexbook file pointer
    \param  username username to find
    \return TRUE on success, FALSE otherwise
 */
int find_username(FILE *fp, char *username){

	char s[25];
	char line[250];
	int f = FALSE;

	do{
		// read until " "
		fscanf(fp,"%[^ ]", s);
		if(strcmp(username, s) == 0)
			f = TRUE;
		else
			// move to the end of line
			fgets(line, 250, fp);
	}while(!feof(fp) && f == 0);

	return f;
}
