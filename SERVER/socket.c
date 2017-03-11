
/*!	\file socket.c
	\author F. Urbinelli federico.urbinelli@gmail.com
	\version 1.0.0
	\date 06/03/2017
*/

#include "socket.h"

/*!	\fn Getaddrinfo
	\brief get information about a host name and/or service and load up a struct sockaddr with the result.
    \param node the host name to connect to, or an IP address
    \param service port number or the name of a particular service like "http" or "ftp"
    \param hints pointer to a struct addrinfo
    \param res pointer to a linked-list of results
    \return ERROR on error, 0 otherwise
 */
int Getaddrinfo(const char *node , const char *service , const struct addrinfo *hints , struct addrinfo **res){

	if(getaddrinfo(node, service, hints, res) != 0){
		perror("Getaddrinfo() error");
		return ERROR;
	}

	return 0;
}

/*! \fn Socket
 	\brief allocate a socket descriptor
    \param domain describes what kind of socket you're interested in (PF_INET or PF_INET6)
    \param type SOCK_STREAM for TCP sockets (our case), SOCK_DGRAM for UDP sockets
    \param protocol which protocol to use with a certain socket type.
    \return ERROR on error, the socket descriptor on success
 */
int Socket(int domain, int type, int protocol){

	int s;

	s = socket(domain, type, protocol);
	if(s == ERROR){
		perror("Socket() error");
		return ERROR;
	}

	return s;
}

/*! \fn Bind
	\brief associate a socket with an IP address and port number
    \param sockfd socket descriptor
    \param my_addr pointer to a struct sockaddr that contains information about our address
    \param addrlen length in bytes of that address
    \return ERROR on error, 0 on success
 */
int Bind(int sockfd, struct sockaddr *my_addr, int addrlen){

	if(bind(sockfd, my_addr, addrlen) < 0){
		perror("Bind() error");
		return ERROR;
	}

	return 0;
}

/*! \fn Connect
 	\brief connect a socket to a server
    \param sockfd socket descriptor
    \param res pointer to linked-list of the address to connect to (see Getaddrinfo)
    \return ERROR on error, 0 on success
 */
int Connect(int sockfd, struct addrinfo **res){

	void *addr;
	struct sockaddr_in *ip;
	char addrstr[INET6_ADDRSTRLEN];
	ip = (struct sockaddr_in * ) (*res)->ai_addr;
	addr = &(ip->sin_addr);
	inet_ntop((*res)->ai_family, addr, addrstr, sizeof(addrstr));

	printf("Trying to connect to %s, port %d ...\n", addrstr, ntohs(((struct sockaddr_in * ) (*res)->ai_addr)->sin_port));
	if(connect(sockfd, (*res)->ai_addr, (*res)->ai_addrlen) < 0){
		perror("Connect() error");
		return ERROR;
	}

	return 0;
}

/*!	\fn Listen
 	\brief tell a socket to listen for incoming connections
    \param sockfd socket descriptor
    \param backlog how many pending connections you can have before the kernel starts rejecting new ones
    \return ERROR on error, 0 on success
 */
int Listen(int sockfd, int backlog){

	if(listen(sockfd, backlog) < 0){
		perror("Listen() error");
		return ERROR;
	}

	return 0;
}

/*! \fn Accept
 	\brief accept an incoming connection on a listening socket
    \param sockfd socket descriptor
    \param addr This is filled in with the address of the site that's connecting to you
    \param addrlen This is filled in with the sizeof() the structure returned in the addr parameter
    \return ERROR on error, socket descriptor of new connection on success
 */
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){

	int newS;

	newS = accept(sockfd, addr, addrlen);
	if(newS < 0){
		perror("Accept() error");
		return ERROR;
	}

	return newS;
}

/*! \fn Send
 	\brief Send data out over a socket
    \param sockfd socket descriptor
    \param msg pointer to data to send
    \param len number of bytes to send
    \param flags set to 0 for normal data
    \return ERROR on error, number of bytes sent on success
 */
int Send(int sockfd, const void *msg, int len, int flags){

	ssize_t bytes_sent;

	if ((bytes_sent = send(sockfd, msg, len, flags)) < 0){
		perror("Send() error");
		return ERROR;
	}

	return bytes_sent;
}

/*! \fn Recv
 	\brief receive data on a socket
    \param sockfd socket descriptor 
    \param buf pointer to buffer
    \param len maximum length of buf
    \param flags set to 0 for normal data
    \return ERROR on error, number of bytes received on success
 */
int Recv(int sockfd, void *buf, int len, int flags){

	ssize_t bytes_rec;

	if((bytes_rec = recv(sockfd, buf, len, flags)) < 0){
		perror("Recv() error");
		return ERROR;
	}

	return bytes_rec;
}

/*! \fn get_in_addr
 	\brief get sockaddr, IPv4 or IPv6
    \param sa address to check
    \return struct sockaddr IPv4/IPv6
 */
void *get_in_addr(struct sockaddr *sa){
	
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/*! \fn bind_server_socket
 	\brief create a socket and bind it
    \param port address port 
    \return ERROR on error, bound socket on success
 */
int bind_server_socket(char *port){

	struct addrinfo hints, *myInfo, *tempAddr;
	int listener;
	int yes=1;        		// for setsockopt() SO_REUSEADDR, below

	// get us a socket and bind it
	memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    Getaddrinfo(NULL, port, &hints, &myInfo);

    // FIND AN ADDRESS TO BIND

    for(tempAddr = myInfo; tempAddr != NULL; tempAddr = tempAddr->ai_next) {
	    listener = Socket(tempAddr->ai_family, tempAddr->ai_socktype, tempAddr->ai_protocol);
    	if (listener < 0) continue;

        // lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (Bind(listener, tempAddr->ai_addr, tempAddr->ai_addrlen) < 0) {
	        close(listener);
            continue;
        }

        break;
    }

    // if we got here, it means we didn't get bound
    if (tempAddr == NULL) {
    	close(listener);
		fprintf(stderr, "selectserver: failed to bind\n");
    	return ERROR;
    }

  	freeaddrinfo(myInfo);

  	return listener;
}

/*! \fn connect_to_server
 	\brief connect to server address
    \param servAddr server address
    \param servPort server port
    \return ERROR on error, socket descriptor on success
 */
int connect_to_server(char *servAddr, char *servPort){

	int s;
	struct addrinfo hints, *serverInfo;		// server info

	memset(&hints, 0, sizeof (hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if(Getaddrinfo(servAddr, servPort, &hints, &serverInfo) == ERROR){
		freeaddrinfo(serverInfo);
		return ERROR;
	}

	s = Socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
	if(s == ERROR){
		close(s);
		freeaddrinfo(serverInfo);
		return ERROR;
	}

	if(Connect(s, &serverInfo) == ERROR){
		close(s);
		freeaddrinfo(serverInfo);
		return ERROR;
	}

	return s;
}

/*!	\fn writen
	\brief send data
	\param sd socket descriptor
	\param b data to send
	\param s size of the data (b)
	\param retry_on_interrupt retry on interrupt (no: 0 / yes: 1)
	\return ERROR on error, 0 otherwise
	\note see <http://stackoverflow.com/a/24260280/7158454>
*/
int writen(const int sd, const char * b, const size_t s, const int retry_on_interrupt){

  size_t n = s;
  while (0 < n){
    ssize_t result = write(sd, b, n);
    if (ERROR == result){
      if ((retry_on_interrupt && (errno == EINTR)) || (errno == EWOULDBLOCK) || (errno == EAGAIN))
        continue;
      else
        break;
    }

    n -= result;
    b += result;
  }

  return (0 < n) ?ERROR :0;
}

/*! \fn readn
	\brief receive data
	\param sd socket descriptor
	\param p buffer
	\param n number of bytes to read
	\return ERROR on error, 0 otherwise
	\note see <http://stackoverflow.com/a/20149925/7158454>
*/
int readn(int sd, void * p, size_t n){

  size_t bytes_to_read = n;
  size_t bytes_read = 0;

  while (bytes_to_read > bytes_read){
    ssize_t result = read(sd, p + bytes_read, bytes_to_read);
    if (ERROR == result){
      if ((EAGAIN == errno) || (EWOULDBLOCK == errno))
        continue;

#   	ifdef DEBUG
    	{
        	int errno_save = errno;
        	perror("read() failed");
        	errno = errno_save;
    	}
#   	endif

      	break;

    }else if(0 == result){
#  		ifdef DEBUG
    	{     
       		int errno_save = errno;
       		fprintf(stderr, "%s: Connection closed by peer.", __FUNCTION__);
        	errno = errno_save;
    	}
#   	endif

    	break;
    }

    bytes_to_read -= result;
    bytes_read += result;
  }

  return (bytes_read < bytes_to_read) ?ERROR :0; 
}

/*!	\fn check_inline_parameters
 	\brief just a primary check
    \param expected expected number of parameters
    \param argc argc from the main()
    \return ERROR on error, 0 on success
 */
int check_inline_parameters(int expected, int argc){

	if(expected != argc){
		printf("%s", lang.s1);
		return ERROR;
	}else{
		return 0;
	}
}
