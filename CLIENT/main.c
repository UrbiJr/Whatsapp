
/*!	\file main.c
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
	\note each function name starts with "ncurses" in order to distinguish them from the other functions
*/

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
#include "in_out.h"
#include "languages.h"
#include "message.h"
#include "mycurses.h"
#include "mytime.h"
#include "socket.h"
#include "user.h"
#include "text.h"

int main(int argc, char *argv[]){

	extern recCurrentLanguage lang;
	int choice, n;
	int timeout;

	FILE *fp;	

	WINDOW *background, *main_window;

	int x, y;								// ncurses
	int logged = FALSE;						// user login status
	int n_unread_mes = 0;					// number of current received messages and not read

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

    define_language(DEFAULT_LANG);

	if(check_inline_parameters(3, argc) == ERROR) exit(EXIT_FAILURE);

	if ((s = connect_to_server(argv[1], argv[2])) == ERROR) exit(EXIT_FAILURE);

	fp = open_file("indexbook.txt", "r");

	/* FIRST THING: UPDATE INDEXBOOK */

	/* receiving file size */
    readn(s, &data_size, 2);

    /* receiving file data */
    err = readn(s, mes_buffer, data_size);
   	if(err != ERROR){
    	FILE *fpin = open_file("indexbook.txt", "w");
    	write_to_file(fpin, mes_buffer, data_size);
        close_file(fpin);
    }else{
        printf("readn() failed receiving file");
    }

	tv.tv_sec = 2;
 	tv.tv_usec = 500000;

 	// START NCURSES MDOE
	ncurses_init();
	ncurses_init_console(&y, &x);
	ncurses_select_language(main_window);
	background = ncurses_background(y, x);
	
	choice = 1;	// highlight first choice by default (see below)

	// main loop
	for(;;){

		FD_ZERO(&read_fds);
		FD_SET(s, &read_fds);

		if(select(s+1, &read_fds, NULL, NULL, &tv) == ERROR){
			close(s);
			delwin(background);
			delwin(main_window);
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
    			FILE *fpin = open_file("message_for_user.txt", "w");
    			write_to_file(fpin, mes_buffer, data_size);
        		close_file(fpin);
        		fpin = open_file("message_for_user.txt", "r");
        		message = read_message_from_file(fpin);
        		close_file(fpin);
        	}else{
        		printf("readn() failed receiving file");
        	}

        	n = ncurses_message_received(main_window);
        	if(n == 0 || n == 2){
        		// ADD MESSAGE TO UNREAD MESSAGES

        		unread_mes[n_unread_mes] = message;
        		n_unread_mes++;

        	}else if(n == 1){
        		// OPEN MESSAGE

        		// delete previous content and display some yellow background here
        		delwin(main_window);
        		main_window = newwin(y-2, 90, 1, COLS/2 - 45);
        		wbkgd(main_window, COLOR_PAIR(YELLOW_YELLOW));
        		wrefresh(main_window);
        		ncurses_read_message(message);
        	}

		}

		/* 
		 *	note, as 3° parameter I pass choice to highlight the last choice
		 *	user made, or anyway where he was where timeout has been reached
		 */

		choice = ncurses_menu(main_window, logged, choice, &timeout);

		if(timeout){
           	timeout = 0;
           	continue;
        }

		switch(choice){

			// login
			case 1:

				// if already logged, tell the server that we change user
				if(logged) writen(s, "1004", sizeof("1004"), 0);

				fp = open_file("indexbook.txt", "r");
				logged = ncurses_login(fp, &user, main_window);
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
				close_file(fp);

				break;

			// indexbook
			case 2:

				fp = open_file("indexbook.txt", "r");
				ncurses_index_book(fp, main_window, users); 
				close_file(fp);
				
				break;

			// send message
			case 3:

				if(logged){

					retry_on_interrupt = 0;
					writen(s, "1002", sizeof("1002"), retry_on_interrupt);

					fp = open_file("indexbook.txt", "r");
					ncurses_send_message(fp, main_window, &user, &message);
					close_file(fp);

					/*
                        for unknown reason we have to delete message.txt
                        then create it again, otherwise sendfile() will send
                        previous version of message.txt
                    */

					remove("message.txt");

					fpout = open_file("message.txt", "w");
					write_message_to_file(fpout, &message);
					close_file(fpout);

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
				while((ncurses_unread_messages(main_window, unread_mes, &n_unread_mes)) != 0);

				break;

			// change language
			case 5:

				ncurses_select_language(main_window);
				background = ncurses_background(y, x);

				break;

			// exit
			case 6:

				writen(s, "1003", sizeof("1003"), 0);
				close(s);
				delwin(background);
				delwin(main_window);
				endwin();
				exit(EXIT_SUCCESS);

				break;
		}
	}

	close(s);
	delwin(background);
	delwin(main_window);
	endwin();
	
	return 0;
}
