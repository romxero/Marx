//This is the main file for the job sender application
#include "libmarx.h"



												



int main(int argc, char **argv)
{
	if (!(argv[1]))
	{ //argument for hostname
		puts("You forgot the hostname!");
		return -1;
	}
	if (!(argv[2]))
	{
		//argument for joblist file
		puts("You forgot the file!");
		return -1;
	}
												//
												if (processConfigFile(&configFileData,defaultConfigFile) < 0)
												{
														puts("No configuration file detected, using default attributes\n");
														defaultTheConfigFileData(&configFileData);	
														//Add the default values to the configuration file data structure
													
												}
	
	FILE *fp = NULL; //the pointer to the jobfile
	char *line = NULL; //char pointer for a line to process
	int jobCount = 0; //the job count is set to zero
	char ch='\0'; //null character as default
	
	size_t len = 0; //helps finding length, a size_t (data type size could change depending on architecture)
	ssize_t read = 0; //for the read buffer

	
	fp=fopen(argv[2], "r") ; //openning the file as read only
	//~ 
	if (fp == NULL)
	{
		//if the pointer is still null then there is no file
		puts("No File");
		return -1;
	}
	
	 while(ch != EOF) {
		 //this loop opens the file and counts how many new line elements are present
		ch=fgetc(fp);
		if(ch=='\n')  
		{
			jobCount++; //the jobcount is incremented to how many new lines are found
		}
	  }
	  fclose(fp); //close the file handle
	  char jobs[jobCount][256]; //create a statice array of characters
	  
	
		fp=fopen(argv[2], "r") ; //open the file again as read only
		
		if (fp == NULL)
		{
			//if null then return -1.. ends the app
			return -1;
		}	  
	  int i = 0; //set a counter to zero.. This is ANSI C and not C99 or C11
	  read = getline(&line, &len, fp); //use getline to read each line of the file
	  while (read != -1) {
			//while read is not -1
               strcpy(jobs[i],line); //copy the string from the getline function to the character array of jobs
               jobs[i][len] = '\0'; //append the array
               ++i; //increment the counter
               read = getline(&line, &len, fp); //call the get line function again
           }
           
           i = 0; //ansi C, reusing counter variable

	 
	   fclose(fp); //close the file handle
	   free(line); //free the line point
	   
	   /* Getting all the client stuff ready */
	uint loopPthreadCounter = 0;
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char boolBreakLoop = -1;
	char *boolBreakLoopPtr = &boolBreakLoop;
	char buffer[256];
	portno = atoi(configFileData.portNum); //easily just assigns the constant port number
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //sets up the socket
	if (sockfd < 0)
	{
		//socket error
	quitWithError("ERROR opening socket");
	}
	
	
		server = gethostbyname(argv[1]); //this function assigns the hostname to the server pointer
		if (server == NULL)
		{
			//host error
		  quitWithError("ERROR, no such host");
		  exit(0);
		}
				
				
				bzero((char *) &serv_addr, sizeof(serv_addr)); //zero out some buffers for the server addresses
				serv_addr.sin_family = AF_INET; //regular tcp networking
				bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length); //buffer copy operation
				serv_addr.sin_port = htons(portno); //set port to connect with host
	
				if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) //this needed to be casted right here
				{
					//error connecting to host
					quitWithError("ERROR connecting");
				}
				
					//~ printf("Please enter the message: ");
					/* Sending and receiving stuff is now here */
				  int sendVar = ZERO_OUT_VALUE; //start out with a zero value
				  int *sendVarPtr = &sendVar;
				  
				  int recieveVar = ZERO_OUT_VALUE; //zero out value
				  int *recieveVarPtr = &recieveVar; //address of pointer
		
				  sendVar = QUEUE_JOBS; //send a queue jobs message
				  
				  send(sockfd,sendVarPtr,sizeof(int),0); //send down the socket
				  //~ SEND_PRIORITY_NUM
				  //~ SEND_DIRECTIVE
				  //~ READY_FOR_JOBS
				  recv(sockfd,recieveVarPtr,sizeof(int),0); //wait for receiving notification
				  if (recieveVar == SEND_PRIORITY_NUM)
				  {
					  sendMessage(sockfd,"3"); //send the priority number
				
				  }
				  
				  recv(sockfd,recieveVarPtr,sizeof(int),0); //wait
				  if (recieveVar == SEND_DIRECTIVE)
				  {
					  //send directive
					  
						sendVar = ROUND_ROBIN;
				  
						send(sockfd,sendVarPtr,sizeof(int),0);
					  
				
				  }
				  
				  recv(sockfd,recieveVarPtr,sizeof(int),0);
				  
				  if (recieveVar == READY_FOR_JOBS)
				  {
					  //now we are ready to send jobs
					  
					   i = 0;
					  for (; i < jobCount; i++)
					  {
						  //send jobs in this for loop to server
						  sendMessage(sockfd,jobs[i]);
						  recv(sockfd,recieveVarPtr,sizeof(int),0);
						   if (recieveVar == RECIEVED_OK)
							{
								//if confirmed, send more
								if (i == (jobCount - 1))
								{
									//if all jobs in list have been reached end the job queueing
									sendVar = QUEUE_JOBS_END;
								}
								else
								{
									//else zero out the old value and send more jobs
									sendVar = ZERO_OUT_VALUE;
								}
								send(sockfd,sendVarPtr,sizeof(int),0);
								
							}
					  }
					  
					
					  
				
				  }
				  
				
				 
				close(sockfd); //close the socket handle
				
				

	}

