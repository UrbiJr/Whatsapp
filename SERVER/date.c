
/*!	\file date.c
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#include "date.h"

/*!	
	\brief set the day
	\param d date
	\param n new day
	\return date
*/
recDate *set_day(recDate *d, int n){
	d->day = n;
	return d;
}

/*!	
	\brief set the month
	\param d date
	\param n new month
	\return date
*/
recDate *set_month(recDate *d, int n){
	d->month = n;
	return d;
}

/*!	
	\brief set the year
	\param d date
	\param n new year
	\return date
*/
recDate *set_year(recDate *d, int n){
	d->year = n;
	return d;
}

/*!	
	\brief get the day
	\param d date
	\return day
*/
int get_day(recDate *d){
	return d->day;
}

/*!	
	\brief get the month
	\param d date
	\return month
*/
int get_month(recDate *d){
	return d->month;
}

/*!	
	\brief get the year
	\param d date
	\return year
*/
int get_year(recDate *d){
	return d->year;
}
