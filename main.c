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


#include <sys/types.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>



#include "constant_definitions.h" //this is used for self modifying code and other things
#include "configFile.h" //for the configuration file

struct configurationFile configFileData; //the configuration file data ~ its easier to keep this data global

#include "data_structures/queue.h" //will only be using the queue library
#include "data_structures/pqueue.h" //priority queue stufff
#include "data_structures/btree.h" //binary tree stuff

#include "etc_functions.h" // misc functions
#include "benchmark.h"
#include "socketConnections.h"

/*Define Constant Macros */

#define appName "Marx Server" //application name
#define appVers ".25" //alpha version 


//~ #define portNumDef "65000" //this is the default port number for the process
//~ #define VARIANCE 500 //this is used for the variaince within searchin of the binary tree
#define defaultConfigFile "/etc/marxd.conf" //this is the default configuration file for the daemon process

char terminateApp = -1; //this is used to terminate the application
char *terminateAppPtr = &terminateApp; //this is a pointer used to terminate the application


void cleanUp()
{
	puts("Goodbye!, Process has been killed");
	terminateApp = 1; //this is just used to break out of the main loop
	
}

struct threadData
{
	int networkSocket;
	BTREE *btreeNode;
	struct priorityQueueContainer mainQueue;
	char *breakLoopPtr;
	
	
};


void *threadWrapper(void *threadParameters)
{
	struct threadData *DataForFunction;
	DataForFunction = (struct threadData *) threadParameters;
	
	//~ serverFunction(DataForFunction->networkSocket,DataForFunction->btreeNode,DataForFunction->mainQueue,DataForFunction->breakLoopPtr); //main server function
	pthread_exit(NULL);
	
}

typedef unsigned int uint; //use this for an unsigned interger

//maybe I should take out the pointer of pointer parmeter in main function

int main(int argc, char **argv)
{
				
				/* Multi-threading stuff */
				int numCPU = sysconf( _SC_NPROCESSORS_ONLN );  
				if (numCPU < 0) {quitWithError("Couldn't get correct CPU count!!");}//this gets the number of cpus
				
				pthread_t threads[numCPU]; //the number of unique threads to implement
				pthread_mutex_t pqueueMutex, peerMutex, killMutex; //three mutexes for multithreading operarions
				uint threadCounter = 0;
				
				struct threadData serverDataForPthreads[numCPU]; //this is used as a wrapper data structure for our message passing functino in a multithreading environment
				
				
				
					/* Configuration and forking stuff */
									
					pid_t pid, sid, cpid; // this is the pid for our daemon process
					
					if (processConfigFile(&configFileData,defaultConfigFile) < 0)
					{
							puts("No configuration file detected, using default attributes\n");
							defaultTheConfigFileData(&configFileData);	
							//Add the default values to the configuration file data structure
						
					}
					
					/* Socket Stuff */ 
					int sockfd, newsockfd, portno; //for socket return values
					struct sockaddr_in serv_addr, cli_addr;
					socklen_t clilen; //socket structures
					
					
					
					/* signal stuff */
					struct sigaction saTerm;
					memset(&saTerm, 0, sizeof(saTerm));
					saTerm.sa_handler = &cleanUp;
					sigaction(SIGTERM, &saTerm, NULL); //this is what happens when the application gets killed
					
					
					
					
					/* Main event loop stuff */
					int (*functionPointer)(); //this is the function pointer used for changing things in the tree stuff	
					static	BTREE rootNode = NULL; //keep this the node name.. have it be a global variable
					
					//~ QUEUE *priorityQueue = NULL; //this is the main priority queue 
					//~ initQueue(&jobQueue,1);
					//~ 
					//~ PQ jobQueue; //this is the priority queue
					//~ initPqueue(&jobQueue); //initialize the queue
					//~ 
					struct priorityQueueContainer jobQueue;
					initializePQueue(&jobQueue);
					int errorTrap; //used to find errors in the code
					
					
								/* Main loop begins below */ 
								sockfd = createAndBindSocket(configFileData.portNum);
								if (sockfd < 0)
								{
									quitWithError("Error creating and binding socket!");
								}
								
								
								errorTrap = listen(sockfd,100); //allows this process to listen on this socket ... 100 connections will wait in a queue
								
								  if (errorTrap < 0)
									{
									  quitWithError("Error listening to binded socket!");
									  
									}
								
								int i = 0;
								
								
								/* For threading */
								//~ for (; i < numCPU; i++)
								//~ {
									//~ serverDataForPthreads[i].networkSocket = -1;
									//~ serverDataForPthreads[i].btreeNode = &rootNode;
									//~ serverDataForPthreads[i].mainQueue = &jobQueue;
									//~ serverDataForPthreads[i].breakLoopPtr = terminateAppPtr;
									//~ 
								//~ }

							while(terminateApp < 0)
							{
								//main loop
								if (threadCounter > numCPU) {threadCounter = 0;} //make sure it goes back to zero
								
									newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
									
									if (newsockfd != -1)
									{
										
										serverDataForPthreads[threadCounter].networkSocket = newsockfd;
										
										errorTrap = serverFunction(newsockfd,&rootNode,&jobQueue,terminateAppPtr); //main server function
											if (errorTrap < 0)
											{
											  puts("Connection error with a peer/client!");
											  
											}
										//~ pthread_create (&threads[threadCounter], NULL, (void *) &threadWrapper, (void *) &serverDataForPthreads[threadCounter]);
										
										
										while (jobQueue.count > 0)
										{
											//inner loop for job queue
											
											if (rootNode == NULL)
											{
												puts("There are no peers connected to the server\n");
												break;
											}
											else
											{
												functionPointer = &launchJobs; //remove all elements
												
												traverseBTree(rootNode,POST_ORDER, jobQueue.head->queueElement, functionPointer);
												pDequeue(&jobQueue); //removes the top element in priority queue
												heartBeatProcess(&jobQueue);
											}
												
												
											
										}
										
										
										threadCounter++; //increment the thread counter
										continue;
										
									}
								
								
									sleep(5); //if the loop ever gets here, we will sleep for 5 seconds
						
							
							}
										
										
						
					/* This is the clean up section outside of the main loop */
					close(sockfd); //close the socket
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


