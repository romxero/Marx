//#define NULL 0
typedef char *DATA; //this is where the data is located at..


struct linkNode
{
	DATA name; //data member in node
	struct node *next; //recursive node left
	struct node *returnToFirst; //recursive node right

	};

typedef struct linkNode LNODE; 
typedef LNODE *LLIST;
// Take this or leave this


LLIST returnLListMem()
{
//this will used to return memory for a binary tree

return malloc(sizeof(LLIST) * 1);
	
}


void addLListValue(LLIST passedNode, char* const string)
{
	 
			passedNode->name = string;
			
}
