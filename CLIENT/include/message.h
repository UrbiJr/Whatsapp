
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"
#include "mytime.h"
#include "user.h"
#include "text.h"

typedef struct{
	recUser sender;
	recUser receiver;
	recDate date;
	recTime time;
	Text text;
}recMessage;

char* getText(recMessage * );
recMessage *setText(recMessage * , char * );
recUser getSender(recMessage * );
recMessage *setSender(recMessage * , recUser * );
recUser getReceiver(recMessage * );
recMessage *setReceiver(recMessage * , recUser * );
recDate getDate(recMessage * );
recMessage *setDate(recMessage * , recDate * );
recTime getTime(recMessage * );
recMessage *setTime(recMessage * , recTime * );
int findMessage(recMessage * , recMessage , int );
int removeMessageFromArray(recMessage * , recMessage , int * );
#endif
