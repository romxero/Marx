//this is for a priority queue
typedef QUEUE *PQUEUE;

struct priQueue
{
	int count; //forgot why I made this an integer type 
	PQUEUE pQueue;
	
};


struct priorityQueue
{
			QUEUE  *queueElement; //the queue element
			
			struct priorityQueue *next; //this is the next element in the queue...
}; //this is the priority queue strucuture

typedef struct priorityQueue pre_pQueue;
typedef pre_pQueue *pQueue;
struct priorityQueueContainer
{
	
	
	pQueue head, tail; //heads and tails of the container
	int count; //this is the count of elements inside of the priority queue
	
	
};

pQueue returnPQueueMem()
{
	return calloc(1, sizeof(pre_pQueue));; //this is used for a pqueue element
	
}

void initializePQueue(struct priorityQueueContainer *root)
{
	root->head = NULL;
	root->tail = NULL;
	root->count = 0;
	
	
}


int pEnqueue(struct priorityQueueContainer *root, QUEUE *passedQueue)
{
		pQueue tempNode = returnPQueueMem();
		tempNode->queueElement = passedQueue;
		tempNode->next = NULL;
		

		
		if (root->count <= 0)
		{
			root->head = root->tail = tempNode;
		}
		
		
		else
		{
		
		
			pQueue rootNode = root->head;
			
			
			
			if( tempNode->queueElement->priority  > rootNode->queueElement->priority )
				{
					tempNode->next = rootNode;
					rootNode = tempNode;
					root->head = rootNode;
					while (rootNode->next != NULL)
					{
						rootNode = rootNode->next;
					}
					
					root->tail = rootNode;
				
					
				}
			else
				{
					for(; rootNode->queueElement->priority > tempNode->queueElement->priority; rootNode = rootNode->next)
					{
						if (rootNode->next->queueElement->priority < tempNode->queueElement->priority)
						{
							tempNode->next = rootNode->next;
							rootNode->next = tempNode;
						}
						
						
					}
					
						if (rootNode->next == NULL)
						{
							tempNode->next = rootNode->next;
							rootNode->next = tempNode;
							
						}
						while (rootNode->next != NULL)
						{
							rootNode = rootNode->next;
						}
						
						root->tail = rootNode;
			
			}
		
		}

		root->count++;
		return 1; //good 	
}

int isPQueueEmpty(struct priorityQueueContainer *root)
{
	if (root->head == NULL)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

	
int pDequeue(struct priorityQueueContainer *root)
{
	if (isPQueueEmpty(root) > 0)
	{
		
		return -1;
	}
	else
	{
				pQueue tempNode = root->head->next;
				free(root->head->queueElement);
				free(root->head);
				root->head = tempNode;
				root->count--;
				if (root->head == NULL)
				{
					root->tail = NULL;
				}
				
					return 1; //good
	}
	
	
}
	
	
	
	
	//############################################################################################

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
					free(pq->QueueArray[0]);
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
				
				
					
				
				
			
