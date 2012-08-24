//#define NULL 0
typedef char *DATA; //this is where the data is located at..


struct node
{
	DATA name; //data member in node
	struct node *left; //recursive node left
	struct node *right; //recursive node right

	};

typedef struct node NODE; 
typedef NODE *BTREE;
// Take this or leave this


BTREE returnTreeMem()
{
//this will used to return memory for a binary tree

return malloc(sizeof(BTREE) * 1);
	
}


void addBtreeValue(BTREE passedNode, char* const string)
{
	 
			passedNode->name = string;
			
}
