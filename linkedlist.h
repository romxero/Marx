//#define NULL 0
typedef char *DATA; //this is just a string
#include "queue.h" //include the queue structure within this file 

struct linkNode
{
	DATA name; //data member in node
	DATA ip_address; //this is used for the ip addressing
	int flop_num; //this is used for floating point numbers from benchmark
	int integer_num; //this is used for integer bearing benchmarks
	int combined_benchmark; //this is used for the combined benchmark scores
	struct linkNode *next; //recursive node left
	struct linkNode *returnToFirst; //recursive node right

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
