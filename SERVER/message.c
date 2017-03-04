
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "message.h"

char* getText(recMessage *a){
	return a->text.string;
}

recMessage *setText(recMessage *a, char *s){
	memset(a->text.string, 0, sizeof (a->text.string));
	strcpy(a->text.string, s);

	return a;
}

recUser getSender(recMessage *a){
	return a->sender;
}

recMessage *setSender(recMessage *a, recUser *m){
	a->sender = *m;

	return a;
}

recUser getReceiver(recMessage *a){
	return a->receiver;
}

recMessage *setReceiver(recMessage *a, recUser *d){
	a->receiver = *d;

	return a;
}
recDate getDate(recMessage *a){
	return a->date;
}

recMessage *setDate(recMessage *a, recDate *d){
	a->date = *d;

	return a;
}

recTime getTime(recMessage *a){
	return a->time;
}

recMessage *setTime(recMessage *a, recTime *t){
	a->time = *t;

	return a;
}

/**
 * returns index of a message if it's found in the array
 * @param  messages array
 * @param  m        message to find
 * @param  n        current number of elements
 * @return          message index on success, -1 otherwise
 */
int findMessage(recMessage *messages, recMessage m, int n){

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
			strcmp(messages[i].text.string, m.text.string) == 0
		){
			return i;
		}
	}

	return -1;
}

/**
 * removes a recMessage struct from array
 * @param  messages array
 * @param  m        message to remove
 * @param  n        current number of elements
 * @return          0 on success, -1 on error
 */
int removeMessageFromArray(recMessage *messages, recMessage m, int *n){
	
	int index = findMessage(messages, m, *n);
	if(index == -1) return -1;


	if(index != (*n - 1))
		memmove(&messages[index], &messages[index+1], ((*n-1)-index) * sizeof(messages[0]));
	memset(&messages[*n-1], 0, sizeof(messages[*n-1]));

	(*n)--;

	return 0;
}
