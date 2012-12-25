typedef unsigned char *QDATA; //queue data

struct qLinkedList
{
	//linked list of queue structure
	QDATA value;
	struct qLinkedList *next;
};


typedef struct qLinkedList QELEMENT;
typedef QELEMENT *QLINK;

struct queue
{
	//the queue container
	QLINK head, tail;
	int numOfElements;
	int directive; //this will be used for directives of the queue
	char priority; //this is the actual priority of the queue
	
};

typedef struct queue QUEUE;

int isQueueEmpty(QUEUE *root)
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

void initQueue(QUEUE *root, char priorityNum, int directivePassed)
{
	//initializes the queue
	root->head = NULL;
	root->tail = NULL;
	root->numOfElements = 0;
	root->priority = priorityNum;
	root->directive = directivePassed;
}

QLINK returnQueueElement()
{
	//returns a queue element
	return calloc(1, sizeof(QELEMENT));
}

void enqueue(QUEUE *root, QDATA var)
{
	//enqueue
	QLINK temp = returnQueueElement();
	temp->value = var; 
	temp->next = NULL;
	if (isQueueEmpty(root) > 0)
	{
		root->head = root->tail = temp;
	}
	else
	{
		root->tail->next = temp;
		root->tail = temp;
	}
	root->numOfElements++;
}

int dequeue(QUEUE *root)
{
	//dequeue
	if (isQueueEmpty(root) > 0)
	{
		
			return -1;
	}
	else
	{
		QLINK temp = root->head->next;
		free(root->head);
		root->head = temp;
		root->numOfElements--;
		if (root->head == NULL)
		{
			root->tail = NULL;
		}
		
	}

}


char* peek(QUEUE *root)
{
	//deprecated
	//peek at the top of the queue
	if (root->head != NULL)
	{
	return root->head->value;
	}
	else
	{
		return NULL; 
	}

}
