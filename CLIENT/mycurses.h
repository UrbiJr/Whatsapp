
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef MYCURSES_H
#define MYCURSES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>

#include "constants.h"
#include "languages.h"
#include "date.h"
#include "mytime.h"
#include "user.h"
#include "message.h"
#include "inOut.h"

// MACRO: returns TRUE if we are using server software, FALSE otherwise.
#define isServerProgram() ((n_choices) == 5 ? TRUE: FALSE) 

enum colors{ GREEN_BLACK = 1, GREEN_AZURE, GREEN_GREEN, MAGENTA_AZURE, YELLOW_AZURE, RED_RED, YELLOW_RED, AZURE_AZURE, RED_BLACK, GREEN_BLUE, BLUE_BLUE, YELLOW_BLUE, RED_YELLOW, BLACK_GREEN, WHITE_BLUE, BLACK_AZURE, WHITE_WHITE, YELLOW_YELLOW, RED_BLUE, BLACK_YELLOW, BLACK_BLACK, RED_WHITE };

char *choices[6];
int n_choices;
// the following two are the y and x sizes to use for the main windows
int mainwin_y;	// window rows
int mainwin_x;	// window columns

void ncurses_init(void );
void ncurses_initColors(void );
void ncurses_initConsole(int *, int *);
WINDOW *ncurses_background(int, int );
int ncurses_menu(WINDOW *, int , int , int * );
void ncurses_printMenu(WINDOW * , int , int , int , int, char *[] , int , int );
int ncurses_login(FILE * , recUser * , WINDOW * );
void ncurses_indexBook(FILE * , WINDOW * , recUser * );
int ncurses_sendMessage(FILE * , WINDOW * , recUser * , recMessage * );
void ncurses_addUser(FILE * , WINDOW * , int * );
int ncurses_deleteUser(FILE * , WINDOW * , int * );
void ncurses_alert(char[] );
int ncurses_message_received(WINDOW * );
int ncurses_interMenu(WINDOW * , int , int , int , int , int , char *[], int );
int ncurses_unread_messages(WINDOW * , recMessage * , int * );
void ncurses_read_message(recMessage );
void ncurses_select_language(WINDOW * );

#endif
