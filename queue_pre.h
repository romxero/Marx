/*This will be a priority queue */ 
/* queue_pre.h */
typedef unsigned int pquint;
	
	
	struct queue{

		char *name; //not sure what to do about this 
		pquint priorityValue; /* This is uses to assess the priorties amongst 
					 the queues */ 
		pquint position; /*this is to tell us 
				the position this value has in the queue */ 
		int fileDescriptor; //this is used for the file descriptor 
		
		struct queue *link; // this is used to get the next queue

}; 


	typedef struct queue QUEUE_PRE;
	typedef QUEUE_PRE *QUEUE; 

void addDataToQueueElement(QUEUE passedQueueNode)
{
	//blah 
}

struct pqueue_pre{
	//I think this is right 
	int numOfItems; /*this tells me how many elements are in the 
				queue*/ 
	QUEUE head; //the front of the queue
	QUEUE tail; //the tail of the queue
	};
typedef struct pqueue_pre pqueue;

QUEUE returnQueueElement()
{
		//this should suffice
		return malloc(sizeof(QUEUE_PRE) * 1 );
		//return a queue element
}
//~ 
//~ pqueue returnPqueueElement()
//~ {
		//~ //this should suffice
		//~ return malloc(sizeof(pqueue) * 1 );
		//~ //return a queue element
//~ }

void initializePqueue(pqueue root)
{
	
		//this will initialize the queue
		root.head = NULL; 
		root.tail = NULL; 

}

int isQueueEmpty(pqueue root)
{
	if (root.head == NULL)
	{
		
		return 1;
	}
	else
	{
		
		return -1;
	}
	
}


void enqueue(pqueue root, char *string, int priority)
{
			//this will initialize the queue
			//~ struct pqueue rootCopy = root; //make a memory copy right here
			QUEUE newQueue = returnQueueElement(); // returns a queue element
			
			newQueue->name = string;
			newQueue->link = NULL;
			newQueue->priorityValue = priority;
			
			if (isQueueEmpty(root) > 0)
			{
			
				root.head = newQueue;
				root.tail = newQueue;
				
			}
			else if(priority > 0)
			{
				//facilitate the priority queue
				newQueue->link = root.head;
				root.head = newQueue; 
				
			}
			else
			{
				root.tail->link = newQueue;
				root.tail = newQueue;
				
			}
			
}



	
int dequeue(pqueue root)
{
		if(isQueueEmpty(root) > 0)
		{
			return -1;
		}
		else
		{
			QUEUE temp = root.head->link;
			root.head->link = NULL;
			free(root.head);
			root.head = temp;

			//do your magic here 
		}
}



char* peek(pqueue root) 
{
	
	return root.head->name;
}

