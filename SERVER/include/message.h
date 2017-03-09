
/*!	\file date.h
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0
	\date 06/03/2017
*/

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
	recText text;
}recMessage;

recText get_text(recMessage * );
recMessage *set_text(recMessage * , recText * );
recUser get_sender(recMessage * );
recMessage *set_sender(recMessage * , recUser * );
recUser get_receiver(recMessage * );
recMessage *set_receiver(recMessage * , recUser * );
recDate get_date(recMessage * );
recMessage *set_date(recMessage * , recDate * );
recTime get_time(recMessage * );
recMessage *set_time(recMessage * , recTime * );
int find_message(recMessage * , recMessage , int );
int remove_message(recMessage * , recMessage , int * );

#endif