#include "libmarx.h"

//~ char const *portNumChar = "65000";

												



int main(int argc, char **argv)
{
	if (!(argv[1]))
	{
		puts("You forgot the hostname!");
		return -1;
	}
	if (!(argv[2]))
	{
		puts("You forgot the file!");
		return -1;
	}
	
												if (processConfigFile(&configFileData,defaultConfigFile) < 0)
												{
														puts("No configuration file detected, using default attributes\n");
														defaultTheConfigFileData(&configFileData);	
														//Add the default values to the configuration file data structure
													
												}
	
	FILE *fp = NULL;
	char *line = NULL;
	int jobCount = 0;
	char ch='\0';
	
	size_t len = 0;
	ssize_t read = 0;

	
	fp=fopen(argv[2], "r") ;
	//~ 
	if (fp == NULL)
	{
		puts("No File");
		return -1;
	}
	
	 while(ch != EOF) {
		ch=fgetc(fp);
		if(ch=='\n')  
		{
			jobCount++;
		}
	  }
	  fclose(fp);
	  char jobs[jobCount][256];
	  
	
		fp=fopen(argv[2], "r") ;
		
		if (fp == NULL)
		{
			return -1;
		}	  
	  int i = 0;
	  read = getline(&line, &len, fp);
	  while (read != -1) {
			
               strcpy(jobs[i],line);
               jobs[i][len] = '\0';
               ++i;
               read = getline(&line, &len, fp);
           }
           
           i = 0;

	 
	   fclose(fp);
	   free(line);
	   /* Getting all the client stuff ready */
	uint loopPthreadCounter = 0;
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char boolBreakLoop = -1;
	char *boolBreakLoopPtr = &boolBreakLoop;
	char buffer[256];
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
		
				  sendVar = QUEUE_JOBS;
				  
				  send(sockfd,sendVarPtr,sizeof(int),0);
				  //~ SEND_PRIORITY_NUM
				  //~ SEND_DIRECTIVE
				  //~ READY_FOR_JOBS
				  recv(sockfd,recieveVarPtr,sizeof(int),0);
				  if (recieveVar == SEND_PRIORITY_NUM)
				  {
					  sendMessage(sockfd,"3");
				
				  }
				  
				  recv(sockfd,recieveVarPtr,sizeof(int),0);
				  if (recieveVar == SEND_DIRECTIVE)
				  {
					  
						sendVar = ROUND_ROBIN;
				  
						send(sockfd,sendVarPtr,sizeof(int),0);
					  //~ sendMessage(sockfd,"procinfo");
				
				  }
				  
				  recv(sockfd,recieveVarPtr,sizeof(int),0);
				  
				  if (recieveVar == READY_FOR_JOBS)
				  {
					  
					  
					   i = 0;
					  for (; i < jobCount; i++)
					  {
						  sendMessage(sockfd,jobs[i]);
						  recv(sockfd,recieveVarPtr,sizeof(int),0);
						   if (recieveVar == RECIEVED_OK)
							{
								if (i == (jobCount - 1))
								{
									sendVar = QUEUE_JOBS_END;
								}
								else
								{
									
									sendVar = ZERO_OUT_VALUE;
								}
								send(sockfd,sendVarPtr,sizeof(int),0);
								
							}
					  }
					  
					
					  
				
				  }
				  
				
				 
				close(sockfd);
				
				
						//~ i = 0;
					//~ for (; i < jobCount; i++)
					  //~ {
						  //~ free(jobs[i]);
						  //~ 
					  //~ }

	}

