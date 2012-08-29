/*Created by Randy White
 * CIS 049
 * 8/25/2012
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
//#include <jemalloc/jemalloc.h> //this is experimental right here 
//replace the original malloc ~ might cause dependencie issues
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/futex.h>
#include <sys/time.h>


#include "tree.h" // this is for the binary ~ non cascade!! 
#include "etc_functions.h" // this is for the binary ~ non cascade!! 

/*Define Constant Macros */

#define appName "Marx" //application name
#define appVers ".01" //alpha version 
#define maxConnections 1024 // this will be used for the maximum connections to this server
#define maxThreads 64 //might increase depending on the processor
#define portNum 3009 //this is the default port number for the process

//~ #include "linkedlist.h" // this is for the linked list data stuff ~ Deprecated, linkedlists structure is included in tree.h!!



//~ char* const directive = 'HELLO';	




typedef unsigned int uint; //use this for an unsigned interger

//maybe I should take out the pointer of pointer parmeter in main function
int main(int argc, char **argv)
{

			if ( argc != 2 ) /* argc should be 2 for correct execution */
			{
				/* We print argv[0] assuming it is the program name */
				
				fprintf(stderr, "Usage: %s <string>\n", argv[0]);
            

				printf( "\n\n\n"); 
				printf( "This program takes to commands issued\n"); 
				printf( "%s : param0\n",argv[0]); 
					exit(EXIT_FAILURE); //this will exit the application


			}
				
			else
			{

				
					
					pid_t pid, sid, cpid; // this is the pid for our daemon process
					int sockfd, newsockfd, portno; //for socket return values
					socklen_t clilen; //socket structures
					char buffer[256]; //character buffer for sockets
					struct sockaddr_in serv_addr, cli_addr;
					int n;
					char buf; //misc buffer
					


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
					
					
					/* socket stuff goes here */
					
							sockfd = socket(AF_INET, SOCK_STREAM, 0); //this sets up the socket structure for TCP connections
								if (sockfd < 0)
								{
								quitWithError("ERROR opening socket");
								}
								bzero((char *) &serv_addr, sizeof(serv_addr)); //initiates a server buffer to zero
								//~ portno = atoi(argv[1]); //just here for reference.. the atio() function converts a string to an integer
								portno = portNum; //this is the port number
								serv_addr.sin_family = AF_INET; //sets the server address as a TCP socket
								serv_addr.sin_port = htons(portno); //sets the port number of the 
								if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) //binds a socket to an address
								{
									quitWithError("ERROR on binding");
								}
								/* Main loop begins below */ 
								
								listen(sockfd,5); //allows this process to listen on this socket
								clilen = sizeof(cli_addr);
								newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
								
							if (newsockfd < 0)
							{
							quitWithError("ERROR on accept");
							}
							bzero(buffer,256);
							n = read(newsockfd,buffer,255);
							if (n < 0)
							{
							 quitWithError("ERROR reading from socket");
							}
							else
							{
							printf("Here is the message: %s",buffer);
							}
							
							n = write(newsockfd,"I got your message",18);
							if (n < 0)
							{
							 error("ERROR writing to socket");
							}							
							while(1)
							{
								
								
								/*This below is really for debugging */
								
							   printf("%s Is the best application ever!\n",appName); //this is used to debug the messages
							   //~ puts(" Is the best application ever!\n"); //hahaha
							   
							
							
								sleep(5); // make sure to sleep.. 5 takes a bunch of cpu hahaha	
							}
							//~this is where execution begins
					
						}
	
	

	
	return 0;
	
	
 
	//this is the end of the line right here,,, make sure to return 0 if everything went right
}

