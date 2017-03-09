
/*!	\file mycurses.h
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0
	\date 06/03/2017
*/

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
#include "time.h"
#include "user.h"
#include "message.h"
#include "in_out.h"

// MACRO: returns TRUE if we are using server software, FALSE otherwise.
#define is_server_program() ((n_choices) == 5 ? TRUE: FALSE) 

enum colors{ GREEN_BLACK = 1, GREEN_AZURE, GREEN_GREEN, MAGENTA_AZURE, YELLOW_AZURE, RED_RED, YELLOW_RED, AZURE_AZURE, RED_BLACK, GREEN_BLUE, BLUE_BLUE, YELLOW_BLUE, RED_YELLOW, BLACK_GREEN, WHITE_BLUE, BLACK_AZURE, WHITE_WHITE, YELLOW_YELLOW, RED_BLUE, BLACK_YELLOW, BLACK_BLACK, RED_WHITE };

char *choices[5];
int n_choices;
// the following two are the y and x sizes to use for the main windows
int mainwin_y;	// window rows
int mainwin_x;	// window columns

void ncurses_init(void );
void ncurses_init_colors(void );
void ncurses_init_console(int *, int *);
WINDOW *ncurses_background(int, int );
int ncurses_menu(WINDOW *, int , int , int * );
void ncurses_print_menu(WINDOW * , int , int , int , int, char *[] , int , int );
int ncurses_login(FILE * , recUser * , WINDOW * );
void ncurses_index_book(FILE * , WINDOW * , recUser * );
int ncurses_send_message(FILE * , WINDOW * , recUser * , recMessage * );
void ncurses_add_user(FILE * , WINDOW * , int * );
int ncurses_delete_user(FILE * , WINDOW * , int * );
void ncurses_alert(char[] );
int ncurses_message_received(WINDOW * );
int ncurses_inter_menu(WINDOW * , int , int , int , int , int , char *[], int );
int ncurses_unread_messages(WINDOW * , recMessage * , int * );
void ncurses_read_message(recMessage );
void ncurses_select_language(WINDOW * );

#endif
