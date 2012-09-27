//this is for a priority queue
typedef QUEUE *PQUEUE;

struct priQueue
{
	int count;
	PQUEUE pQueue;
	
};

typedef struct priQueue pQStruct;

PQUEUE returnPQueueElement()
{
	return calloc(1, sizeof(QUEUE));; //this is used for a pqueue element
	
}
PQUEUE returnPQueueElementSpec(int count)
{
	return calloc(count, sizeof(QUEUE));; //this is used for a pqueue element ~Remember to cast this memory allocator
	
}


int addToPQueueAndSort(struct priQueue *rootStruct, PQUEUE passedQueue )
{
		if (rootStruct->pQueue == NULL) 
		{
			rootStruct->pQueue = returnPQueueElement();
			rootStruct->pQueue[0] = *passedQueue;
			return 1;
			
		}
		//~ else if ( *rootStruct.pQueue != NULL)
		//~ {
			//~ int count = sizeof(*rootQueue)/sizeof(QUEUE); //this is used to count the number of items in array	
			//~ *rootStruct->pQueue = realloc(*rootQueue, sizeof(*rootQueue) + sizeof(QUEUE) * 1);
			//~ qsort(); //implement the qsort algorithm
			//~ return 1;
		//~ }
		//~ else
		//~ {
			//~ 
			//~ 
			//~ return -1;	//it should never get here
		//~ }
		//~ 
	//~ 
	
}


int addQueue(void)
{
	//~ ,PQUEUE passedQueue
	
}
