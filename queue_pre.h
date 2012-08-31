/*This will be a priority queue */ 
typedef unsigned int pquint;
struct queue{

char *name; //not sure what to do about this 

pquint priorityValue; /* This is uses to assess the priorties amongst 
			 the queues */ 

pquint position; /*this is to tell us 
		the position this value has in the queue */ 

int fileDescriptor; //this is used for the file descriptor 

struct queue *link; // this is used to get the next queue

} 



typedef struct queue QUEUE_PRE;
typedef QUEUE_PRE *QUEUE; 

struct pqueue{
	//I think this is right 
	int numOfItems; /*this tells me how many elements are in the 
				queue*/ 
	QUEUE front; //the front of the queue
	QUEUE tail; //the tail of the queue
	};

QUEUE returnQueueElement()
{
		//this should suffice
		return malloc(sizeof(QUEUE) * 1 );
		//return a queue element
}

void addToQueue()
{

}
