
typedef unsigned char* HOSTNAME;


struct linkedList
{
	//the linked list structure
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
	//used to initialize a linked list
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
	//this function adds elements to the list
	LINK tempNode = returnListElement();
	tempNode->hostname = var;
	tempNode->peerSocket = socket;
	tempNode->next = NULL;
	tempNode->front = root;
	
	if (root->next == NULL)
	{
		root->next = tempNode;
		peerCount++; //this is a global variable, should be changed later on.
	}
	else
	{
		while (!(root->next == NULL))
		{
			root = root->next;
		
		}
		root->next = tempNode;
		peerCount++; //this is a global variable, should be changed later on
	}
	
	
}


int removeAllNodes(LINK root)
{
	//removes all elements in list
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
