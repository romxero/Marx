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

#include "data_structures/btree.h"

#include "etc_functions.h" // this is for the binary ~ non cascade!! 
#include "constant_definitions.h" //this is used for self modifying code and other things
#include "socketConnections.h"



/*Define Constant Macros */

#define appName "Marx Server" //application name
#define appVers ".12" //alpha version 
#define maxConnections 1024 // this will be used for the maximum connections to this server
#define maxThreads 64 //might increase depending on the processor
#define portNum "3009" //this is the default port number for the process
#define VARIANCE 500 //this is used for the variaince within searchin of the binary tree
#define defaultConfigFile '/etc/marxd.conf' //this is the default configuration file for the daemon process




void cleanUp()
{
	puts("Goodbye!, Process has been killed");
	
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
					
					BTREE rootNode = newNode();
					rootNode = NULL; //do this to initialize
					
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
					
					//~ 
					
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
							
								//~ bzero(buffer,256);
								
								//~ char* text = (char *) malloc(256 * sizeof(char));
								//~ text = recieveMessage(newsockfd);
								//~ strcpy(text,buffer);
								//~ bzero(text,1024);
								
								char *hostName;
								int sendVar = 0x0000;
								int *sendVarPtr = &sendVar;
								
								int recieveVar = 0x0000;
								int *recieveVarPtr = &recieveVar;
								
								recv(newsockfd,recieveVarPtr,sizeof(int),0);
								
								if (recieveVar == 0xFFFF)
								{
									sendVar = 0xABCD;
									send(newsockfd,sendVarPtr,sizeof(int),0);
									hostName = recieveMessage(newsockfd);
								}
								
								//~ sendMessage(newsockfd,"HOSTNAME\0");
								//~ send(newsockfd,sendVarPtr,sizeof(int),0);
								
								
								
								
								
								char ip[256]; //this is used for the hostname
								char service[20];
								
								socklen_t peerNameLength;
								struct sockaddr_storage peerName;
								
								peerNameLength = sizeof peerName;
								n = getpeername(newsockfd, (struct sockaddr *) &peerName, &peerNameLength);
								struct sockaddr_in *peerFinal = (struct sockaddr_in *) &peerName;
								inet_ntop(AF_INET, &peerFinal->sin_addr,ip,sizeof(ip));
								
								if (n < 0) puts("Couldnt extract hostname");
								close(newsockfd);
							 
							 
							 
							 
							//~ int t = 0;
							while(1)
							{
								
								
					
								
								printf("%s\n",ip); //debug right here
								puts(hostName);
								//~ printf("%s\n",text); //debug right here
								//~ system(buffer); // this is so dangerous right here be very careful/// 
								sleep(2); //dont waste the cpu with this loop/./ yeah
										
								break; //just adding this here for debugging purposes
								
						
							
							}
										
										
						
							//~this is where execution begins
					close(sockfd);
					shutdown(sockfd,SHUT_WR);
					
					
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


