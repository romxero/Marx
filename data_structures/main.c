#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../constant_definitions.h" //this is used for self modifying code and other things
#include "queue.h" //will only be using the queue library
#include "pqueue.h" //priority queue stufff
//~ #include "btree.h" //binary tree stuff


void main()
{
			
			
			
			struct priorityQueueContainer jobQueue;
			initializePQueue(&jobQueue);
			PQUEUE test1 = returnPQueueElement();
			PQUEUE test2 = returnPQueueElement();
			PQUEUE test3 = returnPQueueElement();
			PQUEUE test4 = returnPQueueElement();
			PQUEUE test5 = returnPQueueElement();
			PQUEUE test6 = returnPQueueElement();
			PQUEUE test7 = returnPQueueElement();
			initQueue(test1,1,ROUND_ROBIN);
			initQueue(test2,2,ROUND_ROBIN);
			initQueue(test3,3,ROUND_ROBIN);
			initQueue(test4,4,ROUND_ROBIN);
			initQueue(test5,5,ROUND_ROBIN);
			initQueue(test6,6,ROUND_ROBIN);
			initQueue(test7,7,ROUND_ROBIN);
			pEnqueue(&jobQueue,test1);
			pEnqueue(&jobQueue,test2);
			pEnqueue(&jobQueue,test3);
			pEnqueue(&jobQueue,test4);
			pEnqueue(&jobQueue,test5);
			pEnqueue(&jobQueue,test6);
			pEnqueue(&jobQueue,test7);
			pDequeue(&jobQueue);
			pDequeue(&jobQueue);
			pDequeue(&jobQueue);
			pDequeue(&jobQueue);
			pDequeue(&jobQueue);
			pDequeue(&jobQueue);
			pDequeue(&jobQueue);
			pDequeue(&jobQueue);
			
}
