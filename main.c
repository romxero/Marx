//CREATED BY RANDY WHITE
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
 

#include "tree.h" // this is for the binary ~ non cascade!! 
#include "linkedlist.h" // this is for the linked list data stuff



//~ char* const directive = 'HELLO';	




typedef unsigned int uint; 


int main(int argc, char **argv)
{

			if ( argc != 2 ) /* argc should be 2 for correct execution */
			{
				/* We print argv[0] assuming it is the program name */
				
				fprintf(stderr, "Usage: %s <string>\n", argv[0]);
            

				printf( "\n\n\n\n\n"); 
				printf( "This program takes to commands issued\n"); 
				printf( "%s : param0\n",argv[0]); 
					exit(EXIT_FAILURE); //this will exit the application


			}
				
			else
			{

				
					int pipefd[2]; //this is used to pipe information to this process, most likely control signals
					pid_t pid, sid, cpid; // this is the pid for our daemon process
					
					char buf; //misc buffer
					if (pipe(pipefd) < 0) 
						{
						perror("pipe"); //what the hell is this lol
						exit(EXIT_FAILURE); //exit on failure
						}


					pid = fork(); //fork the proceess to a child process
					
					if(pid < 0)
					{
						printf("ERROR!\n");
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
						exit(EXIT_FAILURE); // exit, things have failed
					}
					
					/* Change the current working directory */
					if ((chdir("/")) < 0) {
					/* Log any failure here */
					exit(EXIT_FAILURE);
					}
					
					/* Close out the standard file descriptors */
					close(STDIN_FILENO);
					close(STDOUT_FILENO);
					close(STDERR_FILENO);
					
						
							//~ root->name = argv[1]; //pass the string through the parmeter 
							//~ root0->name = argv[1]; //pass the string through the parmeter 
							
							
							while(1)
							{
							//infinite loop
							sleep(15); // make sure to sleep	
							}
							//~this is where execution begins
							//proper way for a binary tree
							BTREE root = returnTreeMem(); //new wrapper function that will return a malloc of tree memory-- only 1 element				
							LLIST root0 = returnLListMem(); //these should be encapsulated
						
							//redo this right here and add something cool ... 
							
							
							addBtreeValue(root,argv[1]);
							addLListValue(root0,argv[1]);
							
							printf( "%s\n",root->name);  //this right here will be used to debug everything 	
							printf( "%s\n",root0->name);  //this right here will be used to debug everything 	
							
							free(root); //free the variable	
							free(root0); //free the variable
						
							//end everything here
						
				
						}
	
	

	
	return 0;
	
	
 
	//this is the end of the line right here,,, make sure to return 0 if everything went right
}

