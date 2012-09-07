
typedef unsigned char* HOSTNAME;


struct linkedList
{
	HOSTNAME hostname;
	int peerSocket;
	struct linkedList *next;
	struct linkedList *front;
	
};

typedef struct linkedList ELEMENT;
typedef ELEMENT *LINK;

void initLinkedList(LINK root, HOSTNAME var)
{
	root->next = NULL;
	root->hostname = var;
	root->front = NULL;
}

LINK returnListElement()
{
	return calloc(1,sizeof(ELEMENT));
}

void addElementToList(LINK root, HOSTNAME var)
{
	LINK tempNode = returnListElement();
	tempNode->hostname = var;
	tempNode->next = NULL;
	tempNode->front = root;
	
	if (root->next == NULL)
	{
		root->next = tempNode;
	}
	else
	{
		while (!(root->next == NULL))
		{
			root = root->next;
		
		}
		root->next = tempNode;
	}
	
	
}

int nextNode(LINK root)
{
	
	if (root->next == NULL)
	{
		return -1;
	}
	else
	{
		root = root->next;
	}
	
}

int removeAllNodes(LINK root)
{
	//~ LINK prevNode = returnListElement();
	LINK tmp;
	//~ prevNode = root;
	while (!(root == NULL))
	{
		
		
		tmp = root;
		root = root->next;
		free(tmp);
	}
	//~ if (!(root == NULL))
	//~ {
		//~ 
		//~ free(root);
	//~ }
	
	//~ if (!(prevNode == NULL))
	//~ {
		//~ 
		//~ free(prevNode);
	//~ }
	
}
