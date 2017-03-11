
/*!	\file mysignal.h
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void wait_for_pid(int );

#endif
