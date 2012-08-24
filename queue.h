//this is used for queueing things...

typedef char *DATA; //this is just a string

struct queueNode
{
	DATA name; //data member in node
	//this is ok for now
	struct queueNode *next; //recursive node left
	

	};
