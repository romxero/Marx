/*Created by Randy White
 * CIS 049
 * 8/25/2012
 * Marx Client
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> //make sure to build with param -lpthread
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <errno.h>
#include <syslog.h>
#include <string.h> //make sure the string library is here
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <netdb.h> //this has some structures to pass a host to this to the client program.
#include <sys/epoll.h>

//~ #include "queue.h" //will only be using the queue library
#include "data_structures/queue.h"
#include "etc_functions.h" // this is for the binary ~ non cascade!! 
#include "constant_definitions.h" //this is used for self modifying code and other things
#include "socketConnections.h"
/*Define Constant Macros */

#define appName "Marx Client" //application name
#define appVers ".02" //alpha version 
#define maxConnections 1024 // this will be used for the maximum connections to this server
#define maxThreads 64 //might increase depending on the processor
#define portNum 3009 //this is the default port number for the process
#define defaultConfigFile '/etc/marx.conf' //this is the default file for the client process






int main(int argc, char **argv)
{
	/* Getting all the client stuff ready */
	uint loopPthreadCounter = 0;
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
	portno = portNum; //easily just assigns the constant port number
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
	quitWithError("ERROR opening socket");
	}
	
	
		server = gethostbyname(argv[1]); //this function assigns the hostname to the server pointer
		if (server == NULL)
		{
		  quitWithError("ERROR, no such host");
		  exit(0);
		}
		
				bzero((char *) &serv_addr, sizeof(serv_addr));
				serv_addr.sin_family = AF_INET;
				bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
				serv_addr.sin_port = htons(portno);
	
				if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) //this needed to be casted right here
				{
					quitWithError("ERROR connecting");
				}
				
				printf("Please enter the message: ");
				  bzero(buffer,256);
				  fgets(buffer,255,stdin);
				  n = write(sockfd,buffer,strlen(buffer));
				  if (n < 0)
				  {
					quitWithError("ERROR writing to socket");
					}
				  bzero(buffer,256);
				  n = read(sockfd,buffer,255);
				  if (n < 0)
				  {
					quitWithError("ERROR reading from socket");
					}
				  printf("%s",buffer);
				  
				
				
				
				if (loopPthreadCounter < maxThreads) //this is just a counter from withing the
								{
									loopPthreadCounter++;
								}
								else
								{
									loopPthreadCounter = 0;
								}
								
								return 0;
	//~ printf("This application is the %s, version : %s\n",appName,appVers);
 
}
