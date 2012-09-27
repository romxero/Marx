/*Created by Randy White
	testing the priority queue stuff
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

#include "data_structures/queue.h" //will only be using the queue library
#include "data_structures/pqueue.h" //priority queue stufff





void main()
{
	
	
	struct priorityQueueStructure
	{
	
	
	int count;
	PQUEUE QueueArray[150];
	
	};
	
	typedef struct priorityQueueStructure PQ; //typedefinition
	
					
				   //~ PQUEUE QueueArray = returnPQueueElement();
	void initPqueue(struct priorityQueueStructure *pq)
	{
					int i = 0;
					
						for (; i < 150; i++)
					{
						
						pq->QueueArray[i] = NULL;	
						
					}
					
						pq->count = 0; //make sure to set the count to zero
	}		
			int pQueueAdd(struct priorityQueueStructure *pq, QUEUE *passedQueue)
			{
				
				int i = 0;
					
				for (; i < 150; i++)
				{
						
						
					if (pq->QueueArray[i] == NULL)
					{
						pq->QueueArray[i] = passedQueue;
						
						pq->count++;
						return 1; //this means that the operation was successful
					}	
						
				}
				return -1; //should never get here

				
			}
				
				PQ pq; //this is the priority queue
				initPqueue(&pq);
				QUEUE tempNode; 
				QUEUE tempNode0; 
				QUEUE tempNode1; 

	initQueue(&tempNode,0);
	enqueue(&tempNode,"Hello");
	
	initQueue(&tempNode0,1);
	enqueue(&tempNode0,"Sorry");
	
	initQueue(&tempNode1,2);
	enqueue(&tempNode1,"Bye");
	
	pQueueAdd(&pq,&tempNode);//wait for it
	pQueueAdd(&pq,&tempNode0);//wait for it
	pQueueAdd(&pq,&tempNode1);//wait for it
	
	
	//~ pq.QueueArray[0] = &tempNode;
	//~ pq.QueueArray[1] = &tempNode0;
	//~ pq.QueueArray[2] = &tempNode1;
	//~ 
	
	
	//~ pQStruct rootNode;
	//~ rootNode.pQueue = NULL; // null out the priority queue
	
	//~ PQUEUE rootNode = NULL; //make sure this is null right here
	
	
	
	//~ addToPQueueAndSort(&rootNode,&tempNode);
	//~ addToPQueueAndSort(&rootNode,&tempNode0);
	//~ addToPQueueAndSort(&rootNode,&tempNode1);
   //~ //testing the priority queue implementation
}
