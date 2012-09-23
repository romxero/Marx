//this is for a priority queue
typedef QUEUE *PQUEUE;



PQUEUE returnPQueueElement()
{
	return calloc(1, sizeof(QUEUE));; //this is used for a pqueue element
	
}


int addToPQueueAndSort(PQUEUE rootQueue, PQUEUE passedQueue )
{
		if (rootQueue == NULL)
		{
			rootQueue = returnPQueueElement();
			rootQueue[0] = *passedQueue;
			return 1;
		}
		else if ( rootQueue != NULL)
		{
			int count = sizeof(rootQueue)/sizeof(QUEUE); //this is used to count the number of items in array	
			rootQueue = realloc(rootQueue, sizeof(rootQueue) + sizeof(QUEUE) * 1);
			//~ qsort(); //implement the qsort algorithm
			return 1;
		}
		else
		{
			
			
			return -1;	//it should never get here
		}
		
	
	
}


