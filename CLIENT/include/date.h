
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int day;
	int month;
	int year;
}recDate;

recDate *setDay(recDate * , int );
recDate *setMonth(recDate * , int );
recDate *setYear(recDate * , int );
int getDay(recDate * );
int getMonth(recDate * );
int getYear(recDate * );
#endif
