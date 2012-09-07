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
	//~ char buffer[256];
	//~ bzero(buffer,256);
	char *message = (char *) malloc(256 * sizeof(char));
	int n = 0;
	//~ int strLength;
	//~ strLength = strlen(message);
	n = recv(sockfd,message,256,0); 
	
	if (n < 0) 
	{
		//~ free(message);
		return "null";
		
	
	}
	//~ strcpy(message,buffer);
	return message;
}
