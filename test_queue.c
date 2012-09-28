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
	
	
		void sortThePQueue(struct priorityQueueStructure *pq)
		{
			
			int i = 0;
			int k = 0; //incrementer 
			//~ int k; //incrementer 
				for (; i < pq->count; i++)
				{
						k = 0;
							for (; k < pq->count; k++)
							{
								if(pq->QueueArray[k+1] != NULL)
								{
									
									if(pq->QueueArray[k+1]->priority < pq->QueueArray[k]->priority)
									{
										PQUEUE temp = pq->QueueArray[k];
										pq->QueueArray[k] = pq->QueueArray[k+1];
										pq->QueueArray[k+1] = temp;
										
										
										//finish
									}
								}
							}
							
				}
			//this is used for sorting the p queue
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
				
				
			int removeFromPQueue(struct priorityQueueStructure *pq)
			{
				if (pq->QueueArray[0] == NULL)
				{
					
					return -1;
				}
				
				else if (pq->QueueArray[0]->numOfElements == 0)
				{
					
					pq->QueueArray[0] = NULL;
					
					
				//~ int i = 0;
					//~ 
					//~ for (; i < pq->count ; i++)
					//~ {
						int k = 0;
						for (; k < pq->count ; k++)
						{
								if (pq->QueueArray[k] != NULL)
								{
									pq->QueueArray[k-1] = pq->QueueArray[k];
									pq->QueueArray[k] = NULL;
									
								}
						}
						
					//~ }
					pq->count--; //decrement
					return 1;
				}
				
				else
				{
					
					
					return -1;
				}
				
				
				
			}	
				
				
				
				
				
				
				
				PQ pq; //this is the priority queue
				initPqueue(&pq);
	
				QUEUE tempNode; 
				QUEUE tempNode0; 
				QUEUE tempNode1; 


	initQueue(&tempNode,3);
	enqueue(&tempNode,"Hello");
	
	initQueue(&tempNode0,1);
	enqueue(&tempNode0,"Sorry");
	
	initQueue(&tempNode1,0);
	enqueue(&tempNode1,"Bye");
	
	
	pQueueAdd(&pq,&tempNode);//wait for it
	pQueueAdd(&pq,&tempNode0);//wait for it
	pQueueAdd(&pq,&tempNode1);//wait for it
	sortThePQueue(&pq);
	dequeue(&tempNode1);
	removeFromPQueue(&pq);
	
	dequeue(&tempNode0);
	removeFromPQueue(&pq);
	
	dequeue(&tempNode);
	removeFromPQueue(&pq);
	
}
