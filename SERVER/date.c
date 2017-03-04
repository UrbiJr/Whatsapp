
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "date.h"

recDate *setDay(recDate *a, int n){
	a->day = n;
	return a;
}

recDate *setMonth(recDate *a, int n){
	a->month = n;
	return a;
}

recDate *setYear(recDate *a, int n){
	a->year = n;
	return a;
}

int getDay(recDate *a){
	return a->day;
}

int getMonth(recDate *a){
	return a->month;
}

int getYear(recDate *a){
	return a->year;
}
