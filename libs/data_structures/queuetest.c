#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../constant_definitions.h" //this is used for self modifying code and other things
#include "queue.h" //will only be using the queue library
#include "pqueue.h" //priority queue stufff
//~ #include "btree.h" //binary tree stuff


void main()
{
	
	
	PQUEUE test1 = returnPQueueElement();
	initQueue(test1,0,ROUND_ROBIN);
	enqueue(test1,"hello!");
	enqueue(test1,"two");
	enqueue(test1,"play");
	enqueue(test1,"ok");
	enqueue(test1,"tellme");
	enqueue(test1,"twoah");
	enqueue(test1,"tard");
	dequeue(test1);
	dequeue(test1);
	dequeue(test1);
	dequeue(test1);
	dequeue(test1);
	dequeue(test1);
	dequeue(test1);
	
	dequeue(test1);
	dequeue(test1);
	
}
