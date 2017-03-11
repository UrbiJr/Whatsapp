
/*!	\file mytime.h
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#ifndef MYTIME_H
#define MYTIME_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int minutes;
	int hours;
}recTime;

recTime *set_hours(recTime * , int );
recTime *set_minutes(recTime * , int );
int get_hours(recTime * );
int get_minutes(recTime * );

#endif
