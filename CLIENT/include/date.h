
/*!	\file date.h
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0
	\date 06/03/2017
*/

#ifndef DATE_H
#define DATE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int day;
	int month;
	int year;
}recDate;

recDate *set_day(recDate * , int );
recDate *set_month(recDate * , int );
recDate *set_year(recDate * , int );
int get_day(recDate * );
int get_month(recDate * );
int get_year(recDate * );

#endif
