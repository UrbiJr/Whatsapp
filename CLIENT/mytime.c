
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "mytime.h"

recTime *setHours(recTime *a, int n){
	a->hours = n;
}

recTime *setMinutes(recTime *a, int n){
	a->minutes = n;
}

int getHours(recTime *a){
	return a->hours;
}

int getMinutes(recTime *a){
	return a->minutes;
}
