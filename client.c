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

#include "constant_definitions.h" //this is used for self modifying code and other things
#include "configFile.h" //for the configuration file
struct configurationFile configFileData; //the configuration file data ~ its easier to keep this data global

#include "benchmark.h"
#include "data_structures/queue.h" //will only be using the queue library
#include "data_structures/pqueue.h"
#include "data_structures/btree.h"
 //will only be using the queue library

#include "etc_functions.h" // this is for the binary ~ non cascade!! 

#include "socketConnections.h"

/*Define Constant Macros */

#define appName "Marx Peer" //application name
#define appVers ".05" //alpha version 
#define maxConnections 1024 // this will be used for the maximum connections to this server
#define maxThreads 64 //might increase depending on the processor
//~ #define portNum 65000 //this is the default port number for the process
#define defaultConfigFile "/etc/marx.conf" //this is the default file for the client process
char const *portNumChar = "65000";
char terminateApp = -1; // this is used to terminate the app




int main(int argc, char **argv)
{
	
	if (!(argv[1]))
	{
		puts("You forgot the hostname!");
		return -1;
	}
	/* Getting all the client stuff ready */
	uint loopPthreadCounter = 0;
	int errorTrap = 1; // this is used to catch errors, set it to => 1 to begin with 
	
	if (processConfigFile(&configFileData,defaultConfigFile) < 0)
					{
							puts("No configuration file detected, using default attributes\n");
							defaultTheConfigFileData(&configFileData);	
							//Add the default values to the configuration file data structure
						
					}
	
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char boolBreakLoop = -1;
	char *boolBreakLoopPtr = &boolBreakLoop;
	char buffer[256];
	//~ portno = portNum; //easily just assigns the constant port number
	portno = atoi(configFileData.portNum); //easily just assigns the constant port number
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
				
					//~ printf("Please enter the message: ");
				  int sendVar = ZERO_OUT_VALUE;
				  int *sendVarPtr = &sendVar;
				  
				  int recieveVar = ZERO_OUT_VALUE;
				  int *recieveVarPtr = &recieveVar;

				  sendVar = NEW_PEER;
				  send(sockfd,sendVarPtr,sizeof(int),0);
				  
				  
				while(boolBreakLoop < 0)
				{  
					
					
						peerFunction(sockfd,boolBreakLoopPtr);
				}
				 
				close(sockfd);
				
				

}
