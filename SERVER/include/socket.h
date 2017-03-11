
/*!	\file socket.h
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include "constants.h"
#include "languages.h"

int Getaddrinfo(const char * , const char * , const struct addrinfo * , struct addrinfo ** );
int Socket(int , int , int );
int Bind(int , struct sockaddr * , int );
int Connect(int , struct addrinfo ** );
int Listen(int , int );
int Accept(int , struct sockaddr * , socklen_t * );
int Send(int , const void * , int , int );
int Recv(int , void * , int , int );
void *get_in_addr(struct sockaddr * );
int bind_server_socket(char * );
int connect_to_server(char * , char * );
/* thanks to stackoverflow user @alk for these two goodies (y)(y)(y) */
int writen(const int , const char * , const size_t , const int );
int readn(int , void * , size_t );
int check_inline_parameters(int , int );

#endif
