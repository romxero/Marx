/* this is a test with the epoll() */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> //make sure to build with param -lpthread
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <sys/epoll.h>


#include "tree.h" // this is for the binary ~ non cascade!! 
#include "etc_functions.h" // this is for the binary ~ non cascade!! 
#include "constant_definitions.h" //this is used for self modifying code and other things
#include "socketConnections.h"
/*Define Constant Macros */





void main()
{
	int errorTrap = 0; 
	struct epoll_event ev; //hope this compiles

		int sockfd = createAndBindSocket(3009);	//this is inititating the socket right here 
		
		int newsockfd; //this will be used for the new socket file descriptor
		
	errorTrap = make_socket_non_blocking(sockfd);
			if (errorTrap < 0)
			{
				quitWithError("An issue occurred here"); // hope
				
			}

	
}
