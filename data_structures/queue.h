typedef unsigned char *QDATA;

struct qLinkedList
{
	QDATA value;
	struct qLinkedList *next;
};


typedef struct qLinkedList QELEMENT;
typedef QELEMENT *QLINK;

struct queue
{
	QLINK head, tail;
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

QLINK returnQueueElement()
{
	return malloc(sizeof(QLINK) * 1);
}

void enqueue(QUEUE *root, QDATA var)
{
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
		
	}

}


char* peek(QUEUE *root)
{
	if (root->head != NULL)
	{
	return root->head->value;
	}
	else
	{
		return NULL; 
	}

}
