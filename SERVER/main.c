
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
#include <signal.h>
#include <sys/types.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "connecteduser.h"
#include "constants.h"
#include "date.h"
#include "inOut.h"
#include "languages.h"
#include "message.h"
#include "mycurses.h"
#include "mysignal.h"
#include "mysocket.h"
#include "mytime.h"
#include "user.h"
#include "text.h"

int main(int argc, char *argv[]){

	extern CURR_LANG lang;
	
	recConnectedUser connectedUsers[MAX_CON_USERS]; 	// here I store my connected users
	recMessage messages[MAX_MESSAGES];					// sended messages

	int i, j;  // use these only for the loops

	int i_connections;
	int i_connectedUsers = 0;
	int i_messages = 0;

	pid_t pid;
 	int status1, status2;

    defineLanguage(DEFAULT_LANG);

    if( check_inline_parameters(2, argc) == ERROR ) exit(EXIT_FAILURE);

	if((pid = fork()) < 0){
		perror("main fork() failure");
		exit(EXIT_FAILURE);
	}

 	if(pid == 0){

 		pid = fork();

 		if(pid == 0){

 			/*
			************************************************************************************************ 
									SECOND CHILD: BACKGROUND CONNECTIONS HANDLING
 			************************************************************************************************
 			*/

 			struct sockaddr_storage clientAddr;
			socklen_t addrSize;
			fd_set master;			// master file descriptor list
			fd_set read_fds;		// descriptor list for sockets ready to receive data
			fd_set write_fds;		// descriptor list for sockets ready to send data
			int fdmax;				// maximum file descriptor number
			int listener, newfd;	// our socket and newly accept()ed socket descriptor
			char remoteIP[INET6_ADDRSTRLEN];

             // clear the master and temp sets
			FD_ZERO(&master);
    		FD_ZERO(&read_fds);
    		FD_ZERO(&write_fds);

    		FILE *fpin, *fpout;
    		int fd_fpout;
    		struct stat stat_buf;
    		int sent_bytes = 0;
    		long int offset = 0;
    		int remain_data;

    		uint16_t data_size;

    		char mes_buffer[MAX_BUF_SIZE];
    		int n;
    		char buf[MAX_BUF_SIZE];
        	char str[MAX_BUF_SIZE];
        	int err;
        	int retry_on_interrupt;

            if( ( listener = bind_server_socket(argv[1]) ) == ERROR) exit(EXIT_FAILURE);

    		// listen
    		if (Listen(listener, 10) == -1) {
    			close(listener);
	        	exit(EXIT_FAILURE);
	    	}

    		// add the listener to the master set
    		FD_SET(listener, &master);

    		// keep track of the biggest file descriptor
    		fdmax = listener; // so far, it's this one

    		for(;;){

	    		read_fds = master;
    			write_fds = master;

    			if(select(fdmax+1, &read_fds, &write_fds, NULL, NULL) == -1){
    				close(listener);
    				perror("select()");
    				exit(EXIT_FAILURE);
    			}

    			// run through the existing connections looking for data to read
        		for(i_connections = 0; i_connections <= fdmax; i_connections++) {

        			// "if a socket sended data"
	        		if(FD_ISSET(i_connections, &read_fds)){
	        			if(i_connections == listener){

	        				/* ----- HANDLE NEW CONNECTIONS ----- */

        					addrSize = sizeof(clientAddr);
        					newfd = Accept(listener, (struct sockaddr *)&clientAddr, &addrSize);
        					if(newfd != -1){
	        					FD_SET(newfd, &master);	// add to master set
    	    					if(newfd > fdmax) fdmax = newfd;

                                /* SENDING UPDATED INDEXBOOK */

                                /*
                                    for unknown reason we have to delete indexbook.txt
                                    then create it again, otherwise sendfile() will send
                                    previous version of indexbook.txt
                                */

                                fpin = fopen("indexbook.txt", "r");
                                fpout = fopen("temp.txt", "w");
                                copyFile(fpin, fpout);
                                closeFile(fpin);
                                closeFile(fpout);
                                remove("indexbook.txt");
                                fpin = fopen("temp.txt", "r");
                                fpout = fopen("indexbook.txt", "w");
                                copyFile(fpin, fpout);
                                closeFile(fpin);
                                closeFile(fpout);

                                fd_fpout = open("indexbook.txt", O_RDONLY);
                                fstat(fd_fpout, &stat_buf);
                                data_size = (uint16_t) stat_buf.st_size;

                                /* sending file size */
                                if (-1 == writen(newfd, (char *) &data_size, sizeof(data_size), 1)){
                                    perror("writen() failed writing size");
                                }

                                /* sending file data */
                                remain_data = stat_buf.st_size;
                                offset = 0;
                                while (((sent_bytes = sendfile(newfd, fd_fpout, &offset, data_size)) > 0) &&
                                    (remain_data > 0)){                        
                                    remain_data -= sent_bytes;
                                }

                                close(fd_fpout);

    	    					/*

                                COULD BE USEFUL...

    	    					printf("selectserver: new connection from %s on "
                            		"socket %d\n",
                            		inet_ntop(clientAddr.ss_family,
                                	get_in_addr((struct sockaddr*)&clientAddr),
                                	remoteIP, INET6_ADDRSTRLEN),
                            		newfd);
                            	*/

        					}else{
        						close(newfd);
        					}

        				}else if(readn(i_connections, buf, sizeof("1001")) == 0){

        					/* ----- HANDLE DATA FROM A CLIENT ----- */

        					if(sscanf(buf, "%d%*s", &n) == 1){

        						switch(n){

        							// a user has logged in
        							case 1001:

        								/* receiving the username size */
        								readn(i_connections, &data_size, 2);

        								/* receiving the username */
        								readn(i_connections, str, data_size);

        								if(!alreadyConnected(connectedUsers, i_connectedUsers, str)){
        									setConnectedUsername(&connectedUsers[i_connectedUsers], str);
        									setSock(&connectedUsers[i_connectedUsers], i_connections);
        									i_connectedUsers++;        					
        								}

        								break;

        							// a user has sent a message
        							case 1002:

        								memset(mes_buffer, 0, sizeof(mes_buffer));

        								/* receiving file size */
        								readn(i_connections, &data_size, 2);

        								/* receiving file data */
        								err = readn(i_connections, mes_buffer, data_size);
    									if(err == 0){
    										FILE *fpin = openFile("message.txt", "w");
    										fwrite(mes_buffer, sizeof(char), data_size, fpin);
        									closeFile(fpin);
        									fpin = openFile("message.txt", "r");
        									messages[i_messages] = readMessageFromFile(fpin);
        									closeFile(fpin);
        									i_messages++;
        								}
        								
        								break;

        							// a user has logged out
        							case 1003:

        								i = 0;
        								while(connectedUsers[i].sock != i_connections)	i++;

        								removeConnectedUserFromArray(connectedUsers, connectedUsers[i], &i_connectedUsers);        								

                                        // disconnect
        								FD_CLR(i_connections, &master);
        								close(i_connections);

        								break;

                                    // a client changed user 
                                    case 1004:

                                        // remove user but keep connection

                                        i = 0;
                                        while(connectedUsers[i].sock != i_connections)  i++;

                                        removeConnectedUserFromArray(connectedUsers, connectedUsers[i], &i_connectedUsers); 

                                        break;

        						}	// END switch 
        					}	// END code-based operations checking
        				}	// END analyzing recv()ed data

        			// "if there's a socket ready to receive data"
        			}else if(FD_ISSET(i_connections, &write_fds)){

        				/* CHECKING IF THE CLIENT HAS TO RECEIVE DATA */

        				retry_on_interrupt = 0;
        				for(i = 0; i < i_connectedUsers; i++){
        					for(j = 0; j < i_messages; j++){
        						if(strcmp(messages[j].receiver.username,
        						connectedUsers[i].username) == 0){

        							/* THIS USER HAS TO RECEIVE A MESSAGE */
   
        							remove("message_for_user.txt");

									fpout = openFile("message_for_user.txt", "w");
									writeMessageToFile(fpout, &messages[j]);
									closeFile(fpout);

									fd_fpout = open("message_for_user.txt", O_RDONLY);
									fstat(fd_fpout, &stat_buf);
									data_size = (uint16_t) stat_buf.st_size;

									/* sending file size */
									if (-1 == writen(connectedUsers[i].sock, (char *) &data_size, sizeof(data_size), 1)){
   										perror("writen() failed writing size");
									}

									/* sending file data */
									remain_data = stat_buf.st_size;
									offset = 0;
									while (((sent_bytes = sendfile(connectedUsers[i].sock, fd_fpout, &offset, data_size)) > 0) &&
					 				 (remain_data > 0)){                		
                						remain_data -= sent_bytes;
        							}

									close(fd_fpout);

        							removeMessageFromArray(messages, messages[j], &i_messages);        							

        						}
        					}	// END loop between messages
        				}	// END loop between connected users
        			}	// END handle connection
        		}	// END looping through file descriptors
    		}	// END for(;;) - and you thought it would never happen :')
		}	// END second child process

		/*
		************************************************************************************************ 
								FIRST CHILD: NCURSES GUI, USER SIDE.
 		************************************************************************************************
 		*/

 		FILE *pf;	
		WINDOW *background, *mainWindow;
		int x, y;
		int choice;
        int timeout;
        recUser users[MAX_USERS];   // registered users
		int nUsers;		            // number of registered users
		int n;

        // initialize nUsers
		pf = openFile("indexbook.txt", "r");
		nUsers = storeUsers(pf, users);
        closeFile(pf);

		// START NCURSES MDOE
		ncurses_init();
		ncurses_initConsole(&y, &x);
		ncurses_select_language(mainWindow);	
        background = ncurses_background(y, x);

        choice = 1; // highlight first choice by default (see below)

        // main loop
		for(;;){

            /* 
             *  note, as 3° parameter I pass choice to highlight the last choice
             *  user made, or anyway where he was where timeout has been reached
             */

			choice = ncurses_menu(mainWindow, 0, choice, &timeout);

            if(timeout){
                timeout = 0;
                continue;
            }

			switch(choice){

                // add user
				case 1:

                    pf = openFile("indexbook.txt", "r");
                    ncurses_addUser(pf, mainWindow, &nUsers);
                    closeFile(pf);

					break;

                // delete user
				case 2:

                    pf = openFile("indexbook.txt", "r");
                    ncurses_deleteUser(pf, mainWindow, &nUsers);
                    closeFile(pf);

					break;

                // indexbook
                case 3:

                    pf = openFile("indexbook.txt", "r");
                    ncurses_indexBook(pf, mainWindow, users);
                    closeFile(pf);

                    break;

                // change language
				case 4:

					ncurses_select_language(mainWindow);
					break;
					
                // exit
				case 5:

					kill(pid, SIGTERM);
					delwin(background);
					delwin(mainWindow);
					endwin();
					exit(EXIT_SUCCESS);

					break;
			}
		}

		wait_for_pid(pid);
		delwin(background);
		delwin(mainWindow);
		endwin();
	}

	wait_for_pid(pid);
	
	return 0;
}
