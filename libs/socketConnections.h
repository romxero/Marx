/* socketConnections.h */

static int createAndBindSocket(char const *port)
{
	int socketDescriptor; //this should be returned back once all the processing has taken place
	int sockfd, newsockfd, portno; //for socket return values
	int errorTrap; 
	socklen_t clilen; //socket structures				
	struct sockaddr_in serv_addr, cli_addr;
	
	struct addrinfo *socketAddrInfo; // may use this
	struct addrinfo hints; // may use this
	struct sockaddr *socketAddr; // used for the socket address
	struct addrinfo *result, *rp;
	//~ char *portNum;
	//~ sprintf(portNum, "%d", port);
	
	//~ int portI = atoi(port); //use if changing parameter to char*
	
								bzero((char *) &serv_addr, sizeof(serv_addr)); //initiates a server buffer to zero
								
								portno = atoi(port); //just here for reference.. the atio() function converts a string to an integer
								
								memset(&hints, 0, sizeof(hints));
								hints.ai_family = AF_UNSPEC;
								hints.ai_socktype = SOCK_STREAM;
								hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
								   hints.ai_protocol = 0;          /* Any protocol */
								   hints.ai_canonname = NULL;
								   hints.ai_addr = NULL;
								   hints.ai_next = NULL;

								
								
								//~ serv_addr.sin_family = AF_INET; //sets the server address as a TCP socket
								//~ serv_addr.sin_port = htons(portno); //sets the port number of the
								
								errorTrap = getaddrinfo(NULL, port, &hints, &socketAddrInfo);
								if (errorTrap < 0)
								{
									quitWithError("something happened with establishing the address of this server"); //new way to handle errors
								}
								//~ socketDescriptor = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0); //this sets up the socket structure for TCP connections
								//~ socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); //this sets up the socket structure for TCP connections
								
								rp = socketAddrInfo;
								while(rp != NULL)
								{
								
								socketDescriptor = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol); //this sets up the socket structure for TCP connections
								
								//~ if (socketDescriptor < 0)
									//~ {
										//~ close(socketDescriptor);
									//~ rp = rp->ai_next;
										//~ continue; // return this if there is an error
									//~ }
									
									if (bind(socketDescriptor, rp->ai_addr, rp->ai_addrlen) == 0) //binds a socket to an address
									{
										freeaddrinfo(socketAddrInfo);
										return socketDescriptor;
									}
									//~ close(socketDescriptor);
									rp = rp->ai_next;
									
								}	
	return -1; // if all else fails
}


static int createPeerSocket()
{
	int socketDescriptor; //this should be returned back once all the processing has taken place
	int sockfd, newsockfd, portno; //for socket return values
	int errorTrap; 
	socklen_t clilen; //socket structures				
	struct sockaddr_in serv_addr, cli_addr;
	
	struct addrinfo *socketAddrInfo; // may use this
	struct addrinfo hints; // may use this
	struct sockaddr *socketAddr; // used for the socket address
	struct addrinfo *result, *rp;
	struct hostent *server; //for the server
	
	
	//~ char *portNum;
	//~ sprintf(portNum, "%d", port);
	
	//~ int portI = atoi(port); //use if changing parameter to char*
	
								bzero((char *) &serv_addr, sizeof(serv_addr)); //initiates a server buffer to zero
								
								//~ portno = atoi(port); //just here for reference.. the atio() function converts a string to an integer
								
								memset(&hints, 0, sizeof(hints));
								hints.ai_family = AF_UNSPEC;
								hints.ai_socktype = SOCK_STREAM;
								hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
								   hints.ai_protocol = 0;          /* Any protocol */
								   hints.ai_canonname = NULL;
								   hints.ai_addr = NULL;
								   hints.ai_next = NULL;
							
			
			
								rp = socketAddrInfo;
								while(rp != NULL)
								{
								
								socketDescriptor = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol); //this sets up the socket structure for TCP connections
								
								if (socketDescriptor < 0)
									{
										close(socketDescriptor);
										rp = rp->ai_next;
										continue; // return this if there is an error
									}
									else
									{
										
										freeaddrinfo(socketAddrInfo);
										return socketDescriptor;
									}
									//~ 
									
								}	
	return -1; //if this function returns -1, then there is a problem setting up the socket
}


//this right here might redundant if I dont set no blocking in the creation and binding function
static int
make_socket_non_blocking (int sfd)
{
  int flags, s;

  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1)
    {
      perror ("fcntl");
      return -1;
    }

  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1)
    {
      perror ("fcntl");
      return -1;
    }

  return 0;
}


int sendMessage(int sockfd,char const *message)
{
	int n = 0;
	int strLength;
	strLength = strlen(message);
	n = send(sockfd,message,strLength,0); 
	
	if (n < 0) 
	{
		return -1;
	
	}
	return 0;
	
}

char* recieveMessage(int sockfd)
{
	char buffer[256];
	bzero(buffer,256);
	//~ char *message = (char *) malloc(256 * sizeof(char));
	int n = 0;
	//~ int strLength;
	//~ strLength = strlen(message);
	n = recv(sockfd,buffer,256,0); 
	
	if (n < 0) 
	{
		//~ free(message);
		return "null";
		
	
	}
	char *message = (char *) malloc(n * sizeof(char)); //make this the same size as recieved data
	buffer[n] = '\0';
	strcpy(message,buffer);
	//~ char *message = buffer;
	
	return message;
}
/* These are wrapper functions for the mundane tasks */ 



/* End of wrapper functions for mundane tasks */
//REMEMBER TO ADD DEFAULTS TO switch statements!!

int serverFunction(int socket, BTREE *root, struct priorityQueueContainer *jobQueue, char *loopVar)
{
	
								//these are where the server functions are
								int errorTrap = 1; //sets the error trap to 1, so things wont get hairy below when we first start
								
								int sendVar = ZERO_OUT_VALUE;
								int *sendVarPtr = &sendVar;
								
								int recieveVar = ZERO_OUT_VALUE;
								int *recieveVarPtr = &recieveVar;
								int (*functionPointer)(); //this is the function pointer used for changing things in the tree stuff
								errorTrap = recv(socket,recieveVarPtr,sizeof(int),0);
								switch(recieveVar)
								{
									case NEW_PEER:
									{
									sendVar = SEND_HOSTNAME;
									errorTrap = send(socket,sendVarPtr,sizeof(int),0);
									if (errorTrap < 0)
									{
										return -1;
										//an error happened
									}
									char *hostName;
									int returnedBenchScore = 1000;
									hostName = recieveMessage(socket);
									if (hostName == "null")
									{
										return -1;
										//an error happened
									}
									//send for the benchscore
									
									sendVar = SEND_BENCHSCORE;
									errorTrap = send(socket,sendVarPtr,sizeof(int),0);
										if (errorTrap < 0)
									{
										return -1;
										//an error happened
									}
									recieveVar = ZERO_OUT_VALUE;
									
									errorTrap = recv(socket,recieveVarPtr,sizeof(int),0);
										if (errorTrap < 0)
									{
										return -1;
										//an error happened
									}
									returnedBenchScore = recieveVar; //this is used for benchscore
									
									recieveVar = ZERO_OUT_VALUE;
										if (*root == NULL)
										{
											*root = newNode();
											bTreeInit(*root,returnedBenchScore,hostName,socket);
										}
										else
										{
											
											int (*functionPointer)();
											functionPointer = &addHostnameToBTree;
											errorTrap  = searchBtree(*root,returnedBenchScore,hostName,configFileData.variance,socket,functionPointer);
											if (errorTrap < 0)
											{
													//searching did not produce a good variance so a new tree node is to be added
												//add a new node
												addToTree(*root,returnedBenchScore,hostName,socket);
											}
											
											
											
										}
									
									
									ramDiskFileHandle = fopen(ramDiskFile, "a"); //open the file
									if (ramDiskFileHandle == NULL)
									{
										puts("Error writing to RAMDISK! No ramdisk file will be written");
										break; //exit out of this
										
									}
									char buffer[128]; //this buffer is to write strings to the output
									int len = 0; //string length
									len = sprintf(buffer, "Hostname : %s - Benchmark Value : %d\n",hostName,returnedBenchScore);
									buffer[len] += '\0'; // add the terminating character
									fputs(buffer,ramDiskFileHandle); //write lines to the file
									
									fclose(ramDiskFileHandle); //close the file handle
									break;
									}
									case QUEUE_JOBS:
									{
										
										//queue jobs right here
										char *jobs;
										char priorityNumber;
										int directive;
										
										sendVar = SEND_PRIORITY_NUM; //send the priority of tasks
										errorTrap = send(socket,sendVarPtr,sizeof(int),0);
											if (errorTrap < 0)
											{
												return -1;
												//an error happened
											}
										errorTrap = recv(socket,recieveVarPtr,sizeof(int),0);
											if (errorTrap < 0)
											{
												return -1;
												//an error happened
											}
										priorityNumber = (char)recieveVar;
										
										
										sendVar = SEND_DIRECTIVE;
										errorTrap = send(socket,sendVarPtr,sizeof(int),0);
										if (errorTrap < 0)
										{
											return -1;
											//an error happened
										}
										errorTrap = recv(socket,recieveVarPtr,sizeof(int),0);
										if (errorTrap < 0)
										{
											return -1;
											//an error happened
										}
										directive = recieveVar;
										
										sendVar = READY_FOR_JOBS;
										errorTrap = send(socket,sendVarPtr,sizeof(int),0);
											if (errorTrap < 0)
											{
												return -1;
												//an error happened
											}
										
										//~ //use these for recieving ok
										//~ sendVar = RECIEVED_OK;
										//~ errorTrap = send(socket,sendVarPtr,sizeof(int),0);
										//~ 
										PQUEUE tempQueue = returnPQueueElement();
										
										initQueue(tempQueue,priorityNumber,directive);
										
										recieveVar = ZERO_OUT_VALUE;
										
										while(recieveVar != QUEUE_JOBS_END)
										{
												jobs = recieveMessage(socket);
												if (jobs == "null")
												{
													//~ sendVar = RECIEVED_ERROR;
													errorTrap = send(socket,sendVarPtr,sizeof(int),0);
												}
												enqueue(tempQueue,jobs);
												
												sendVar = RECIEVED_OK;
												errorTrap = send(socket,sendVarPtr,sizeof(int),0);
												if (errorTrap < 0)
													{
														return -1;
														//an error happened
													}
									//~ #define RECIEVED_OK 0x0004 //this should be very important			
												
												//~ enqueue(jobQueue,recieveMessage(socket));
												
												//~ errorTrap = recv(socket,recieveVarPtr,sizeof(int),0);
												//~ if (recieveVar == CONTINUE_ADDING_TO_QUEUE)
												//~ {
													//~ continue;
												//~ }
												errorTrap = recv(socket,recieveVarPtr,sizeof(int),0);
											
										}
										
										pEnqueue(jobQueue,tempQueue);
				
				
										//~ recieveVar = ZERO_OUT_VALUE;
										//~ errorTrap = recv(socket,recieveVarPtr,sizeof(int),0);
										//~ 
										//~ if (recieveVar == DISTRIBUTE_SPECIFIER)
										//~ {
											//~ //more to do here
											//~ 
										//~ }
										//~ else if (recieveVar == DISTRIBUTE_ROUND_ROBIN)
										//~ {
											//~ while (!(peek(jobQueue) == "null"))
											//~ {
													//~ 
													//~ functionPointer = &launchJobs; //remove all elements
			//~ 
													//~ traverseBTree(*root,POST_ORDER, peek(jobQueue), functionPointer);
													//~ dequeue(jobQueue);
												//~ 
												//~ 
											//~ }
											//~ 
										//~ }
										
										close(socket); //make sure you close the socket because this is just initiating a job
										
										break;
									}
									case KILL_SERVER:
									{
										*loopVar = 1;
										break;
									}
									case DISPLAY_PEERS:
									{
										
										break;
									}
									default:
									{
										return -1; //this means garbage was recieved
											break;
									} 
									
									
								}
								
								sendVar = ZERO_OUT_VALUE;
								recieveVar = ZERO_OUT_VALUE;
	
	
}

int peerFunction(int socket, char *loopVar)
{
	
							
								//this function is for peers
								int errorTrap = 1;
								
								int sendVar = ZERO_OUT_VALUE;
								int *sendVarPtr = &sendVar;
								
								int recieveVar = ZERO_OUT_VALUE;
								int *recieveVarPtr = &recieveVar;
								
								errorTrap = recv(socket,recieveVarPtr,sizeof(int),0);
											if (errorTrap < 0)
											{
												return -1;
												//an error happened
											}
								 switch(recieveVar)
								{
									case SEND_HOSTNAME:
									{
									errorTrap = sendMessage(socket,getenv("HOSTNAME"));
									if (errorTrap < 0)
											{
												return -1;
												//an error happened
											}
									break;
									}
									case SEND_BENCHSCORE:
									{
										//~ sendVar = benchMark(); //deprecated
										sendVar = configFileData.benchscore; //get benchscore from config file
										errorTrap = send(socket,sendVarPtr,sizeof(int),0);
										if (errorTrap < 0)
											{
												return -1;
												//an error happened
											}
										break; 
									}
									case SEND_JOB:
									{
									char *job = recieveMessage(socket);
									if (job == "null")
									{
											sendVar = RECIEVED_ERROR;
											errorTrap = send(socket,sendVarPtr,sizeof(int),0);
											if (errorTrap < 0)
											{
												return -1;
												//an error happened
											}
										
									}
									else
									{
											sendVar = RECIEVED_OK;
											errorTrap = send(socket,sendVarPtr,sizeof(int),0);
											if (errorTrap < 0)
											{
												return -1;
												//an error happened
											}
											errorTrap = system(job); //the job gets launched here
													if (errorTrap < 0)
													{
														//an error has been sent
															
													}
													else
													{
														//something over here	
														
													}
										
									}
									
										free(job); //free the string
									break;
									
									}
									case KILL_PEER:
									{
										*loopVar = 1;	
										break;
										
									}
									case SEND_CPULOAD:
									{
										//this is used to send the load value of the cpu 
										
										double load[3];
										errorTrap = getloadavg(load, 3);
										if (errorTrap == -1)
										{
											//something bad happened here!!
											return -1;
										}
										//double avg = (load[0] + load[1] + load[2]) / 3;
										float loadAvg = ((float) load[0] + (float) load[1] + (float) load[2]) / 3;
										errorTrap = send(socket,&loadAvg,sizeof(float),0);
										if (errorTrap < 0)
											{
												return -1;
												//an error happened
											}
										
										break;
										
									}
									default:
									{
										return -1; //this means garbage was recieved
											break;
									} 
								}
								
								
								sendVar = ZERO_OUT_VALUE;
								recieveVar = ZERO_OUT_VALUE;
	
	
}
