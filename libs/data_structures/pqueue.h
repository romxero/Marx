

//this is for a priority queue
typedef QUEUE *PQUEUE;

//the priority constants
char const NO_PRIORITY = 0x00;
char const LOW_PRIORITY = 0x01;
char const MED_PRIORITY = 0x02;
char const HIGH_PRIORITY = 0x03;

struct priorityQueue
{
			QUEUE  *queueElement; //the queue element
			int heartBeats; //this is used check if the 
			struct priorityQueue *next; //this is the next element in the queue...
			char currentPriority;
			
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

void heartBeatProcess(struct priorityQueueContainer *root);
void heartBeat(struct priorityQueueContainer *root);

void initializePQueue(struct priorityQueueContainer *root)
{
	//initialize the pqueue
	root->head = NULL;
	root->tail = NULL;
	root->count = 0;
	//~ root
	
	
}


int pEnqueue(struct priorityQueueContainer *root, QUEUE *passedQueue)
{
		//enqueues an element with priorities
		
		pQueue tempNode = returnPQueueMem();
		tempNode->queueElement = passedQueue;
		tempNode->currentPriority = tempNode->queueElement->priority;
		tempNode->heartBeats = 0; //this is used to tell how long a priority queue should be in there before its placed on top
		tempNode->next = NULL;
		

		
		if (root->count <= 0)
		{
			root->head = root->tail = tempNode;
		}
		
		
		else
		{
		
		
			pQueue rootNode = root->head;
			
			
			
			//~ if( tempNode->queueElement->priority  >= rootNode->queueElement->priority )
			if( tempNode->currentPriority  >= rootNode->currentPriority )
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
					for(; rootNode->currentPriority > tempNode->currentPriority; rootNode = rootNode->next)
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
		
		
		//Below is used to increment the heartbeats
		tempNode = root->head;
		
		
				while(tempNode != NULL)
				{
					tempNode->heartBeats++; //increase heartbeats for all of the nodes.
					
					tempNode = tempNode->next;
				}
				
				tempNode = NULL;
			
		
		
		return 1; //good 	
}

int isPQueueEmpty(struct priorityQueueContainer *root)
{
	//checks to see if the queue is empty
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
	//dequeue an element
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
	
void heartBeatProcess(struct priorityQueueContainer *root)
{
	//re-queues elements depending on the heart beats
		pQueue tempNode = root->head;
		pQueue rootNodeCopy = root->head;
		pQueue rootNode = root->head;
		
		
		//~ while(tempNode != NULL)
		//~ {
			//~ tempNode->heartBeats++; //increase heartbeats for all of the nodes.
			//~ 
			//~ tempNode = tempNode->next;
		//~ }
		//~ 
	//~ 
		int i = 0;
		
		for (; i < root->count; i++)
		{
				rootNodeCopy = root->head;
				rootNode = root->head;
				tempNode = NULL;
				
						while(rootNodeCopy != NULL)
						{
							if (rootNodeCopy->next != NULL)
							{
									if (rootNodeCopy->next->heartBeats >= 5 )
									{
										
										tempNode = rootNodeCopy->next;
										tempNode->currentPriority = 5;
										tempNode->heartBeats = 0; // reset the heart beats
										
										rootNodeCopy->next = rootNodeCopy->next->next;
									
										if( tempNode->currentPriority  >= rootNode->currentPriority )
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
												
											for(; rootNode->currentPriority > tempNode->currentPriority; rootNode = rootNode->next)
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
										//
										break;
										
									}
							}
							
							rootNodeCopy = rootNodeCopy->next;
						}
			
		}
		
		
		
		
}
	
	
void heartBeat(struct priorityQueueContainer *root)
{
	//this increases the heartbeats
	pQueue tempNode = root->head;
		while(tempNode != NULL)
		{
			tempNode->heartBeats++; //increase heartbeats for all of the nodes.
			
			tempNode = tempNode->next;
		}
		
	
}

	//############################################################################################




