#include "libmarx.h"


//~ void *threadWrapper(void *threadParameters)
//~ {
	//~ struct threadData *DataForFunction;
	//~ DataForFunction = (struct threadData *) threadParameters;
	//~ 
	//~ serverFunction(DataForFunction->networkSocket,DataForFunction->btreeNode,DataForFunction->mainQueue,DataForFunction->breakLoopPtr); //main server function
	//~ pthread_exit(NULL);
	//~ 
//~ }



//maybe I should take out the pointer of pointer parmeter in main function

int main(int argc, char **argv)
{
				
				if (argc == 1)
					{
						
						quitWithError(appUsageString); //shows application usage
					}
				
				/* Multi-threading stuff */
				int numCPU = sysconf( _SC_NPROCESSORS_ONLN );  
				if (numCPU < 0) {quitWithError("Couldn't get correct CPU count!!");}//this gets the number of cpus
				
				pthread_t threads[numCPU]; //the number of unique threads to implement
				pthread_mutex_t pqueueMutex, peerMutex, killMutex; //three mutexes for multithreading operarions
				uint threadCounter = 0;
				
				//~ struct threadData serverDataForPthreads[numCPU]; //this is used as a wrapper data structure for our message passing functino in a multithreading environment
				
				
				
					/* Configuration and forking stuff */
									
					
					

					
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
					
					int errorTrap; //used to find errors in the code
					
					if(strcmp(argv[1],"-p") == 0) //peer condition
					//~ if(argv[1])
					{
						if (!(argv[2]))
						{
							quitWithError("You forgot the hostname!");
		
							
						}
						else 
						{
							
												if (processConfigFile(&configFileData,defaultConfigFile) < 0)
												//~ if (processConfigFile(&configFileData,"marxd.conf") < 0)
												{
														puts("No configuration file detected, using default attributes\n");
														defaultTheConfigFileData(&configFileData);	
														//Add the default values to the configuration file data structure
													
												}
							if(configFileData.benchscore == -1)
							{
								puts("Uh-oh no saved benchscore, running benchmark now.. this may take awhile..");
								
								configFileData.benchscore = benchMark(); //run the benchmark function
								
								if (writeBenchScoreToConfig(&configFileData,defaultConfigFile) < 0 )
								{
									puts("An error occured writing to the config file! The file might not exist!");
									
								}
								
							}
							
							startDaemonMode(); //start as a daemon now
							
							
							struct hostent *server; //to signify the server element
							portno = atoi(configFileData.portNum); //easily just assigns the constant port number
	
								sockfd = socket(AF_INET, SOCK_STREAM, 0);
								//~ sockfd = createPeerSocket();
								if (sockfd < 0)
								{
								quitWithError("ERROR opening socket");
								}
								
								
									server = gethostbyname(argv[2]); //this function assigns the hostname to the server pointer
									if (server == NULL)
									{
									  quitWithError("ERROR, no such host");

									  
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
				  
				  
				while(terminateApp < 0)
				{  
					
					
						peerFunction(sockfd,terminateAppPtr);
				}
										
										close(sockfd); //close the socket
										shutdown(sockfd,SHUT_WR); 
							
						}
					
						//this is where the peer stuff goes
						
					}
					else if(strcmp(argv[1],"-s") == 0)
					{
						
											if (processConfigFile(&configFileData,defaultConfigFile) < 0)
											{
													puts("No configuration file detected, using default attributes\n");
													defaultTheConfigFileData(&configFileData);	
													//Add the default values to the configuration file data structure
												
											}
							startDaemonMode(); //start as a daemon now
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
					
								//this is for the server process
								
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
										
										//~ serverDataForPthreads[threadCounter].networkSocket = newsockfd;
										
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
										
					}
					else
					{
						quitWithError(appUsageString); //shows application usage
						
					}					
						
			
			
					
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


