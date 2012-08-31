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

#define appName "Marx Server" //application name
#define appVers ".10" //alpha version 
#define maxConnections 1024 // this will be used for the maximum connections to this server
#define maxThreads 64 //might increase depending on the processor
#define portNum 3009 //this is the default port number for the process

#define defaultConfigFile '/etc/marxd.conf' //this is the default configuration file for the daemon process
//~ #include "linkedlist.h" // this is for the linked list data stuff ~ Deprecated, linkedlists structure is included in tree.h!!



//~ char* const directive = 'HELLO';	




typedef unsigned int uint; //use this for an unsigned interger

//maybe I should take out the pointer of pointer parmeter in main function
int main(int argc, char **argv)
{

		

				
					
					pid_t pid, sid, cpid; // this is the pid for our daemon process
					int sockfd, newsockfd, portno; //for socket return values
					socklen_t clilen; //socket structures
					char buffer[256]; //character buffer for sockets
					struct sockaddr_in serv_addr, cli_addr;
					int n;
					char buf; //misc buffer
					uint loopPthreadCounter = 0;
					int errorTrap; 
				
				
					pid = fork(); //fork the proceess to a child process
					
					if(pid < 0)
					{
						printf("ERROR!\n");
						quitWithError("Could not get a PID for child process"); //new way to handle errors

						exit(EXIT_FAILURE); // exit, things have failed
					}
					
					if(pid > 0)
					{
						//Things have succeeded
						exit(EXIT_SUCCESS); // exit, things have failed
					}
					
					umask(0); //change the file mask
					
					sid = setsid(); //get a set id for child process
						
						
					if(sid < 0)
					{
						printf("ERROR!\n");
						quitWithError("Could not get a SID for child process"); //new way to handle errors
						exit(EXIT_FAILURE); // exit, things have failed
					}
					
					/* Change the current working directory */
					if ((chdir("/")) < 0) {
					/* Log any failure here */
					exit(EXIT_FAILURE);
					}
					//closes the standard display stuff
					/* Close out the standard file descriptors */
					close(STDIN_FILENO);
					//close(STDOUT_FILENO); //standard output
					close(STDERR_FILENO);
					
					
					
								/* Main loop begins below */ 
								sockfd = createAndBindSocket(portNum);
								if (sockfd < 0)
								{
									quitWithError("Error creating and binding socket!");
								}
								
								
								errorTrap = listen(sockfd,5); //allows this process to listen on this socket
								
								  if (errorTrap < 0)
									{
									  quitWithError("Error listening to binded socket!");
									  
									}
								
							newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
							bzero(buffer,256);
								
							//~ recv(newsockfd,buffer,256,0);
							
							 n = recv(newsockfd,buffer,255,0);
							 if (n < 0) error("ERROR reading from socket");
							 
							 n = send(newsockfd,"I got your message",18,0);
							 if (n < 0) error("ERROR writing to socket");
							 close(newsockfd);
							 close(sockfd);
							
							while(1)
							{
								
								
								
								//~ printf("Here is the message: %s\n",buffer);
								//~ printf("%s\n",buffer);
								//~ 
								
								
								system(buffer); // this is so dangerous right here be very careful/// 
								sleep(5); //dont waste the cpu with this loop/./ yeah
										
										
								if (loopPthreadCounter < maxThreads) //this is just a counter from withing the
								{
									loopPthreadCounter++;
								}
								else
								{
									loopPthreadCounter = 0;
								}
							
							}
										
										
										
								/*This below is really for debugging */
								//~ printf("This application is the %s, version : %s\n",appName,appVers);
							   //~ printf("%s Is the best application ever!\n",appName); //this is used to debug the messages
							   //~ puts(" Is the best application ever!\n"); //hahaha
								
								
							
								
							
							//~this is where execution begins
					
					
						return 0;

						}
	
	

	
	
	
 
	//this is the end of the line right here,,, make sure to return 0 if everything went right


