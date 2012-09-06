typedef unsigned int DATA;

struct linkedList
{
	DATA value;
	struct linkedList *next;
};


typedef struct linkedList ELEMENT;
typedef ELEMENT *LINK;

struct queue
{
	LINK head, tail;
	int numOfElements;
	
};

typedef struct queue QUEUE;

int isQueueEmpty(QUEUE *root)
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

void initQueue(QUEUE *root)
{
	root->head = NULL;
	root->tail = NULL;
	root->numOfElements = 0;
}

LINK returnQueueElement()
{
	return malloc(sizeof(LINK) * 1);
}

void enqueue(QUEUE *root, DATA var)
{
	LINK temp = returnQueueElement();
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
	
	if (isQueueEmpty(root) > 0)
	{
			return -1;
	}
	else
	{
		LINK temp = root->head->next;
		free(root->head);
		root->head = temp;
		root->numOfElements--;
		
	}

}


int peek(QUEUE *root)
{
	return root->head->value;
}
