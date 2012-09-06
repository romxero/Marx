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
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <sys/epoll.h>


#include "tree.h" // this is for the binary ~ non cascade!! 
#include "etc_functions.h" // this is for the binary ~ non cascade!! 
#include "constant_definitions.h" //this is used for self modifying code and other things
#include "socketConnections.h"
#include "queue_pre.h" //try this out in compilation


void main()
{
	//~ pqueue root = returnPqueueElement();
	pqueue root;
	initializePqueue(root); //initialize this
	enqueue(root,"hello",0);
	
	enqueue(root,"Yo",0);
	char *string = peek(root);
	
	puts(string);
	
}
