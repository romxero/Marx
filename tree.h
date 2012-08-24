#include "linkedlist.h" // this is for the linked list data stuff
//#define NULL 0
typedef char *DATA; //this is where the data is located at..


struct node
{
	DATA name; //data member in node
	DATA unique_id; //this can be used for a unigue identifier
	int integer_range; //used for a range of integer benchmarks
	int flops_range; //used for a range of floating benchmarks
	LLIST to_a_linked_list; //try this out for the circular linked lists
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
