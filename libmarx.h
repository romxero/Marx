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



#include "libs/constant_definitions.h" //this is used for self modifying code and other things
#include "libs/configFile.h" //for the configuration file

struct configurationFile configFileData; //the configuration file data ~ its easier to keep this data global
typedef unsigned int uint; //use this for an unsigned interger
uint peerCount = 0; //peer count

#include "libs/data_structures/queue.h" //will only be using the queue library
#include "libs/data_structures/pqueue.h" //priority queue stufff
#include "libs/data_structures/btree.h" //binary tree stuff

#include "libs/etc_functions.h" // misc functions
#include "libs/benchmark.h"
#include "libs/socketConnections.h"

/*Define Constant Macros */





#define defaultConfigFile "marxd.conf" //this is the default configuration file for the daemon process

char terminateApp = -1; //this is used to terminate the application
char *terminateAppPtr = &terminateApp; //this is a pointer used to terminate the application



void cleanUp()
{
	//this voided function is for a signal handle
	puts("Democracy is the road to socialism.\n\n Marx server/peer going down\n");
	terminateApp = 1; //this is just used to break out of the main loop
	
}

struct threadData
{
	//this threading stuff will be used for the next generation of Marx
	int networkSocket;
	BTREE *btreeNode;
	struct priorityQueueContainer mainQueue;
	char *breakLoopPtr;
	
	
	
};

pid_t pid, sid, cpid; // this is the pid for our daemon process

void startDaemonMode(void)
{
	/* Daemon stuff below*/
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
					if ((chdir(configFileData.directory)) < 0) {
					/* Log any failure here */
					
					quitWithError("Directory Doesn't Exist!! Edit the configuration file");
					//~ exit(EXIT_FAILURE);
					}
					//closes the standard display stuff
					/* Close out the standard file descriptors */
					close(STDIN_FILENO);
					//close(STDOUT_FILENO); //standard output
					close(STDERR_FILENO);
					//~ 
}
