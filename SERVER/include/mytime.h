
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef MYTIME_H
#define MYTIME_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int minutes;
	int hours;
}recTime;

recTime *setHours(recTime * , int );
recTime *setMinutes(recTime * , int );
int getHours(recTime * );
int getMinutes(recTime * );

#endif
