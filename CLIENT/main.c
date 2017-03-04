
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <netdb.h>

#include "constants.h"
#include "date.h"
#include "inOut.h"
#include "languages.h"
#include "message.h"
#include "mycurses.h"
#include "mysocket.h"
#include "mytime.h"
#include "user.h"
#include "text.h"

int main(int argc, char *argv[]){

	extern CURR_LANG lang;
	int choice, n;
	int timeout;

	FILE *pf;	

	WINDOW *background, *mainWindow;

	int x, y;					// ncurses
	int logged = FALSE;			// user login status
	int n_unread_mes = 0;		// number of current received messages and not read

	recUser users[MAX_USERS];				// registered users
	recUser user;
	recMessage unread_mes[MAX_MESSAGES];	// messages received and not read
	recMessage message;					

    int s;									// server socket

    FILE *fpout;
    FILE *fpin;
    int fd_fpout;
    struct stat stat_buf;
    int sent_bytes = 0;
    long int offset = 0;
    int remain_data;
    int retry_on_interrupt;

    uint16_t data_size;
    char mes_buffer[MAX_BUF_SIZE];
    int err;

 	fd_set read_fds;
 	struct timeval tv;

 	FD_ZERO(&read_fds);
	FD_SET(s, &read_fds);

    defineLanguage(DEFAULT_LANG);

	if( check_inline_parameters(3, argc) == ERROR ) exit(EXIT_FAILURE);

	if ( (s = connect_to_server(argv[1], argv[2]) ) == ERROR ) exit(EXIT_FAILURE);

	pf = openFile("indexbook.txt", "r");

	/* FIRST THING: UPDATE INDEXBOOK */

	/* receiving file size */
    readn(s, &data_size, 2);

    /* receiving file data */
    err = readn(s, mes_buffer, data_size);
   	if(err != ERROR){
    	FILE *fpin = openFile("indexbook.txt", "w");
    	writeToFile(fpin, mes_buffer, data_size);
        closeFile(fpin);
    }else{
        printf("readn() failed receiving file");
    }

	tv.tv_sec = 2;
 	tv.tv_usec = 500000;

 	// START NCURSES MDOE
	ncurses_init();
	ncurses_initConsole(&y, &x);
	ncurses_select_language(mainWindow);
	background = ncurses_background(y, x);
	
	choice = 1;	// highlight first choice by default (see below)

	// main loop
	for(;;){

		FD_ZERO(&read_fds);
		FD_SET(s, &read_fds);

		if(select(s+1, &read_fds, NULL, NULL, &tv) == ERROR){
			close(s);
			delwin(background);
			delwin(mainWindow);
			endwin();
			perror("select()");
			exit(EXIT_FAILURE);
		}

		if(FD_ISSET(s, &read_fds)){

			/* THERE'S SOME DATA FOR US */

			memset(mes_buffer, 0, sizeof(mes_buffer));

        	/* receiving file size */
        	readn(s, &data_size, 2);

        	/* receiving file data */
        	err = readn(s, mes_buffer, data_size);
    		if(err != ERROR){
    			FILE *fpin = openFile("message_for_user.txt", "w");
    			writeToFile(fpin, mes_buffer, data_size);
        		closeFile(fpin);
        		fpin = openFile("message_for_user.txt", "r");
        		message = readMessageFromFile(fpin);
        		closeFile(fpin);
        	}else{
        		printf("readn() failed receiving file");
        	}

        	n = ncurses_message_received(mainWindow);
        	if(n == 0 || n == 2){
        		// ADD MESSAGE TO UNREAD MESSAGES

        		unread_mes[n_unread_mes] = message;
        		n_unread_mes++;

        	}else if(n == 1){
        		// OPEN MESSAGE

        		// delete previous content and display some yellow background here
        		delwin(mainWindow);
        		mainWindow = newwin(y-2, 90, 1, COLS/2 - 45);
        		wbkgd(mainWindow, COLOR_PAIR(YELLOW_YELLOW));
        		wrefresh(mainWindow);
        		ncurses_read_message(message);
        	}

		}

		/* 
		 *	note, as 3° parameter I pass choice to highlight the last choice
		 *	user made, or anyway where he was where timeout has been reached
		 */

		choice = ncurses_menu(mainWindow, logged, choice, &timeout);

		if(timeout){
           	timeout = 0;
           	continue;
        }

		switch(choice){

			// login
			case 1:

				// if already logged, tell the server that we change user
				if(logged) writen(s, "1004", sizeof("1004"), 0);

				pf = openFile("indexbook.txt", "r");
				logged = ncurses_login(pf, &user, mainWindow);
				if(logged){
					retry_on_interrupt = 0;
					writen(s, "1001", sizeof("1001"), retry_on_interrupt);

					/* sending username size */
					data_size = (uint16_t) sizeof(user.username);
					if (ERROR == writen(s, (char *) &data_size, sizeof(data_size), 1)){
   						perror("writen() failed writing size");
					}

					/* sending username */
					writen(s, user.username, data_size, retry_on_interrupt);
				}
				closeFile(pf);

				break;

			// indexbook
			case 2:

				pf = openFile("indexbook.txt", "r");
				ncurses_indexBook(pf, mainWindow, users); 
				closeFile(pf);
				
				break;

			// send message
			case 3:

				if(logged){

					retry_on_interrupt = 0;
					writen(s, "1002", sizeof("1002"), retry_on_interrupt);

					pf = openFile("indexbook.txt", "r");
					ncurses_sendMessage(pf, mainWindow, &user, &message);
					closeFile(pf);

					/*
                        for unknown reason we have to delete message.txt
                        then create it again, otherwise sendfile() will send
                        previous version of message.txt
                    */

					remove("message.txt");

					fpout = openFile("message.txt", "w");
					writeMessageToFile(fpout, &message);
					closeFile(fpout);

					fd_fpout = open("message.txt", O_RDONLY);
					fstat(fd_fpout, &stat_buf);
					data_size = (uint16_t) stat_buf.st_size;

					/* sending file size */
					if (ERROR == writen(s, (char *) &data_size, sizeof(data_size), 1)){
   						perror("writen() failed writing size");
					}

					/* sending file data */
					remain_data = stat_buf.st_size;
					offset = 0;
					while (((sent_bytes = sendfile(s, fd_fpout, &offset, data_size)) > 0) &&
					 (remain_data > 0)){                		
                		remain_data -= sent_bytes;
        			}

					close(fd_fpout);

				}else{
					ncurses_alert(lang.s2);
				}

				break;

			// unread messages
			case 4:

				// keep in this window until user wants to exit
				while((ncurses_unread_messages(mainWindow, unread_mes, &n_unread_mes)) != 0);

				break;

			// change language
			case 5:

				ncurses_select_language(mainWindow);
				background = ncurses_background(y, x);

				break;

			// exit
			case 6:

				writen(s, "1003", sizeof("1003"), 0);
				close(s);
				delwin(background);
				delwin(mainWindow);
				endwin();
				exit(EXIT_SUCCESS);

				break;
		}
	}

	close(s);
	delwin(background);
	delwin(mainWindow);
	endwin();
	
	return 0;
}
