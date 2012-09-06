/* socketConnections.h */

static int createAndBindSocket(int const port)
{
	int socketDescriptor; //this should be returned back once all the processing has taken place
	int sockfd, newsockfd, portno; //for socket return values
	int errorTrap; 
	socklen_t clilen; //socket structures				
	struct sockaddr_in serv_addr, cli_addr;
	//~ int portI = atoi(port); //use if changing parameter to char*
	
								bzero((char *) &serv_addr, sizeof(serv_addr)); //initiates a server buffer to zero
								//~ portno = atoi(argv[1]); //just here for reference.. the atio() function converts a string to an integer
								
								serv_addr.sin_family = AF_INET; //sets the server address as a TCP socket
								serv_addr.sin_port = htons(port); //sets the port number of the
								
								//~ socketDescriptor = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0); //this sets up the socket structure for TCP connections
								socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); //this sets up the socket structure for TCP connections
	
								if (socketDescriptor < 0)
									{
										return -1; // return this if there is an error
									}
									
									if (bind(socketDescriptor, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) //binds a socket to an address
									{
										return -1;
									}
									
	return socketDescriptor; // if all else fails
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
