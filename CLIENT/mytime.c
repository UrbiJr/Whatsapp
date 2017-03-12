
/*!	\file mytime.c
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#include "mytime.h"

/*! 
	\brief set the hours of a time
	\param t time
	\param n new hours
	\return time (t)
*/
recTime *set_hours(recTime *t, int n){
	t->hours = n;
}

/*! 
	\brief set the minutes of a time
	\param t time
	\param n new minutes
	\return time (t)
*/
recTime *set_minutes(recTime *t, int n){
	t->minutes = n;
}

/*! 
	\brief get the hours of a time
	\param t time
	\return hours of the time 
*/
int get_hours(recTime *t){
	return t->hours;
}

/*! 
	\brief get the minutes of a time
	\param t time
	\return minutes of the time 
*/
int get_minutes(recTime *t){
	return t->minutes;
}
