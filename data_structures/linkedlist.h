
typedef unsigned char* HOSTNAME;


struct linkedList
{
	HOSTNAME hostname;
	int peerSocket;
	char blacklist; //this is used to black list a server
	struct linkedList *next;
	struct linkedList *front;
	
};

typedef struct linkedList ELEMENT;
typedef ELEMENT *LINK;

void initLinkedList(LINK root, HOSTNAME var, int socket)
{
	root->next = NULL;
	root->hostname = var;
	root->blacklist = 0;
	root->peerSocket = socket;
	root->front = NULL;
}

LINK returnListElement()
{
	return calloc(1,sizeof(ELEMENT));
}

void addElementToList(LINK root, HOSTNAME var, int socket)
{
	LINK tempNode = returnListElement();
	tempNode->hostname = var;
	tempNode->peerSocket = socket;
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
