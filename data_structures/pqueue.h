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
			
			
			
			if( tempNode->queueElement->priority  >= rootNode->queueElement->priority )
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
						if (rootNode->next->queueElement->priority <= tempNode->queueElement->priority)
						{
							tempNode->next = rootNode->next;
							rootNode->next = tempNode;
							break; //break out of the loop for safeness
						}
						
						
					}
					
						if (rootNode->next == NULL)
						{
							tempNode->next = rootNode->next;
							rootNode->next = tempNode;
							
						}
						//this right here goes to the end of the linked list and adds it to tail
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
	
//~ typedef struct priQueue pQStruct;

PQUEUE returnPQueueElement()
{
	return calloc(1, sizeof(QUEUE));; //this is used for a pqueue element
	
}
	
	
	
	//############################################################################################




