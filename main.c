/*Created by Randy White
 * CIS 049
 * 8/25/2012
 * Marx Server
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
#include <signal.h>

#include <linux/futex.h>
#include <sys/time.h>
#include <sys/epoll.h>


#include <sys/types.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//~ 
//~ #include "tree.h" // this is for the binary ~ non cascade!! 
#include "constant_definitions.h" //this is used for self modifying code and other things
#include "data_structures/queue.h" //will only be using the queue library
#include "data_structures/btree.h"

#include "etc_functions.h" // this is for the binary ~ non cascade!! 

#include "socketConnections.h"
#include "benchmark.h"


/*Define Constant Macros */

#define appName "Marx Server" //application name
#define appVers ".20" //alpha version 
#define maxConnections 1024 // this will be used for the maximum connections to this server
#define maxThreads 64 //might increase depending on the processor
#define portNum "65000" //this is the default port number for the process
#define VARIANCE 500 //this is used for the variaince within searchin of the binary tree
#define defaultConfigFile '/etc/marxd.conf' //this is the default configuration file for the daemon process




void cleanUp()
{
	puts("Goodbye!, Process has been killed");
	
	//put stuff in here so that we can deallocate the memory inside of this application
	
	//~ functionPointer = &freeMemInBTree; //remove all elements
			//~ 
	//~ traverseBTree(rootNode,POST_ORDER,functionPointer);
	
}






typedef unsigned int uint; //use this for an unsigned interger

//maybe I should take out the pointer of pointer parmeter in main function
int main(int argc, char **argv)
{

		

				
					
					pid_t pid, sid, cpid; // this is the pid for our daemon process
					int sockfd, newsockfd, portno; //for socket return values
					socklen_t clilen; //socket structures
					char buffer[256]; //character buffer for sockets
					struct sockaddr_in serv_addr, cli_addr;
					
					/* signal stuff */
					struct sigaction saTerm;
					memset(&saTerm, 0, sizeof(saTerm));
					saTerm.sa_handler = &cleanUp;
					sigaction(SIGTERM, &saTerm, NULL);
					
					//~ struct socklen_t client_size;
					int n;
					char buf; //misc buffer
					uint loopPthreadCounter = 0;
					int errorTrap; 
					int (*functionPointer)(); //this is the function pointer used for changing things in the tree stuff
					
					static	BTREE rootNode = NULL; //keep this the node name.. have it be a global variable
					QUEUE jobQueue;
					initQueue(&jobQueue);
					
					char boolBreakLoop = -1;
					char *boolBreakLoopPtr = &boolBreakLoop;
					
					
								/* Main loop begins below */ 
								sockfd = createAndBindSocket(portNum);
								if (sockfd < 0)
								{
									quitWithError("Error creating and binding socket!");
								}
								
								
								errorTrap = listen(sockfd,100); //allows this process to listen on this socket ... 100 connections will wait in a queue
								
								  if (errorTrap < 0)
									{
									  quitWithError("Error listening to binded socket!");
									  
									}
								

							while(boolBreakLoop < 0)
							{
								
									newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
									
									if (newsockfd != -1)
									{
										
										
										serverFunction(newsockfd,&rootNode,&jobQueue,boolBreakLoopPtr); //main server function
									
										continue;
										
									}
								
								
									sleep(5);
						
							
							}
										
										
						
							//~this is where execution begins
					close(sockfd);
					shutdown(sockfd,SHUT_WR);
					//~ free(hostName);
					functionPointer = &freeMemInBTree; //remove all elements
			
					traverseBTree(rootNode,POST_ORDER, NULL, functionPointer);
					
						return 0;
						
						
						}
	
	

	/*
	 * 
	 * Change the linked list to accomodate socket descriptors within this application
	 * 
	 * 
	 * 
	 * */
	
	
 
	//this is the end of the line right here,,, make sure to return 0 if everything went right


