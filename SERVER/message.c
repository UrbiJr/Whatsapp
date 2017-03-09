
/*! \file message.c
    \author F. Urbinelli federico.urbinelli@gmail.com
    \version 1.0
    \date 06/03/2017
*/

#include "message.h"

/*! \fn get_text
	\brief get the text (recText) of a message
	\param m message
	\return text
*/
recText get_text(recMessage *m){
	return m->text;
}

/*! \fn set_text
	\brief set the text (recText) of a message
	\param m message
	\param t new text
	\return message
*/
recMessage *set_text(recMessage *m, recText *t){
	m->text = *t;

	return m;
}

/*! \fn get_sender
	\brief get the sender (recUser) of a message
	\param m message
	\return message sender
*/
recUser get_sender(recMessage *m){
	return m->sender;
}

/*!	\fn set_sender
	\brief set the sender (recUser) of a message
	\param m message
	\param u new sender
	\return message
*/
recMessage *set_sender(recMessage *m, recUser *u){
	m->sender = *u;

	return m;
}

/*! \fn get_receiver
	\brief get the receiver (recUser) of a message
	\param m message
	\return message receiver
*/
recUser get_receiver(recMessage *m){
	return m->receiver;
}

/*!	\fn set_receiver
	\brief set the receiver (recUser) of a message
	\param m message
	\param u new receiver
	\return message
*/
recMessage *set_receiver(recMessage *m, recUser *u){
	m->receiver = *u;

	return m;
}

/*!	\fn get_date
	\brief get the date (recDate) of a message
	\param m message
	\return date of the message
*/
recDate get_date(recMessage *m){
	return m->date;
}

/*!	\fn set_date
	\brief set the date (recDate) of a message
	\param m message
	\param d new date
	\return message
*/
recMessage *set_date(recMessage *m, recDate *d){
	m->date = *d;

	return m;
}

/*!	\fn get_time
	\brief get the time (recTime) of a message
	\param m message
	\return time of the message
*/
recTime get_time(recMessage *m){
	return m->time;
}

/*!	\fn set_time
	\brief set the time (recTime) of a message
	\param m message
	\param t new time
	\return message
*/
recMessage *set_time(recMessage *m, recTime *t){
	m->time = *t;

	return m;
}

/**
 * returns index of a message if it's found in the array
    \param messages array
    \param m message to find
    \param n current number of elements
    \return message index on success, -1 otherwise
 */
int find_message(recMessage *messages, recMessage m, int n){

	int i;

	for(i = 0; i < n; i++){
		if (strcmp(messages[i].sender.username, m.sender.username) == 0 &&
			strcmp(messages[i].sender.password, m.sender.password) == 0 &&
			strcmp(messages[i].sender.name, m.sender.name) == 0 &&
			strcmp(messages[i].sender.surname, m.sender.surname) == 0 &&
			strcmp(messages[i].receiver.username, m.receiver.username) == 0 &&
			strcmp(messages[i].receiver.password, m.receiver.password) == 0 &&
			strcmp(messages[i].receiver.name, m.receiver.name) == 0 &&
			strcmp(messages[i].receiver.surname, m.receiver.surname) == 0 &&
			messages[i].date.day == m.date.day &&
			messages[i].date.month == m.date.month &&
			messages[i].date.year == m.date.year &&
			messages[i].time.minutes == m.time.minutes &&
			messages[i].time.hours == m.time.hours &&
			strcmp(get_string(&messages[i].text), get_string(&m.text)) == 0
		){
			return i;
		}
	}

	return -1;
}

/*!	\fn remove_message
	\brief removes a recMessage struct from array
    \param messages array
    \param m message to remove
    \param n current number of elements
    \return 0 on success, -1 on error
 */
int remove_message(recMessage *messages, recMessage m, int *n){
	
	int index = find_message(messages, m, *n);
	if(index == -1) return -1;

	if(index != (*n - 1))
		memmove(&messages[index], &messages[index+1], ((*n-1)-index) * sizeof(messages[0]));

	memset(&messages[*n-1], 0, sizeof(messages[*n-1]));

	(*n)--;

	return 0;
}
