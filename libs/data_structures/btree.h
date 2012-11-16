//#define NULL 0
#include "linkedlist.h"

typedef int DATA; //this is where the data is located at..


/* These are used as self modifiers in the code */

const char POST_ORDER = 0x00; 
const char PRE_ORDER = 0x01; 
const char INORDER = 0x02; 

struct node
{
	DATA benchscore; //data member in node
	LINK serverList;
	struct node *left; //recursive node left
	struct node *right; //recursive node right

};

typedef struct node NODE; 
typedef NODE *BTREE;
// Take this or leave this


BTREE newNode()
{
	return calloc(1, sizeof(NODE));
}

void bTreeInit(BTREE root, DATA passedValue, HOSTNAME hostnameForServerList, int socket)
{
			//~ root = newNode();
			root->benchscore = passedValue;
			root->left = NULL;
			root->right = NULL;
			root->serverList = returnListElement();
			
			initLinkedList(root->serverList, hostnameForServerList, socket);
	
}


void releaseBTreeData(BTREE root)
{	
	free(root->serverList);
	free(root); //free
}

int freeMemInBTree(BTREE root)
{
	removeAllNodes(root->serverList);
	
	free(root);
}


void traverseBTree(BTREE root, const char DIRECTIVE, PQUEUE jobs, int (*functionPointer)(BTREE root, PQUEUE jobs))
{
		
		if (root != NULL)
		{
			if (DIRECTIVE == INORDER)
			{
				traverseBTree(root->left,DIRECTIVE, jobs, functionPointer);
				//Functionality here
				(*functionPointer)(root,jobs);
				traverseBTree(root->right,DIRECTIVE, jobs, functionPointer);
			}
			else if (DIRECTIVE == POST_ORDER)
			{
				traverseBTree(root->left,DIRECTIVE, jobs, functionPointer);
				traverseBTree(root->right,DIRECTIVE, jobs, functionPointer);
				//Functionality here
				(*functionPointer)(root,jobs);
				
			}
			else if (DIRECTIVE == PRE_ORDER)
			{
				(*functionPointer)(root,jobs);
				//Functionality here
				traverseBTree(root->left,DIRECTIVE, jobs, functionPointer);
				traverseBTree(root->right,DIRECTIVE, jobs, functionPointer);
				
			}
			else
			{
				/* Else just do inorder */ 
				traverseBTree(root->left,DIRECTIVE, jobs, functionPointer);
				//Functionality here
				(*functionPointer)(root,jobs);
				traverseBTree(root->right,DIRECTIVE, jobs, functionPointer);
				
			}
		
		
		}



}


void addToTree(BTREE root, DATA passedValue, HOSTNAME hostnameForServerList, int socket)
{
	
	BTREE tempNode = newNode();
	bTreeInit(tempNode,passedValue,hostnameForServerList, socket);
	
	//Might need to add some functions for adding things to list
	
	if (root == NULL) 
	{
		root = tempNode;
		
	}	

				while(1)
				{
					if (passedValue >= root->benchscore)
					{	//Right
						
						
							if (root->right == NULL)
									{
										root->right = tempNode;
										break;
									}
									else
									{
										root = root->right;
									}
					}
					
				if (passedValue <= root->benchscore)
					{	//Left
						
						
							if (root->left == NULL)
									{
										root->left = tempNode;
										break;
									}
									else
									{
										root = root->left;
									}
					}
					
				
			}
				
				
				
}




int searchBtree(BTREE root, int benchData, HOSTNAME hostname, int variance, int socket, int (*functionPointer)(BTREE root, HOSTNAME hostname, int socket))
{
	int minBench = (benchData - variance);
	
	int maxBench = (benchData + variance);
	
	if (!(root == NULL))
	{
			while(!(root == NULL))
			{	
					if (root->benchscore == benchData)
					{
						(*functionPointer)(root,hostname,socket);
						return 1;
						
					}
					else if (root->benchscore >= minBench & root->benchscore <= benchData)
					{
						(*functionPointer)(root,hostname,socket);
						return 1;
						
					}
					else if (root->benchscore <= maxBench & root->benchscore >= benchData)
					{
						(*functionPointer)(root,hostname,socket);
						return 1;
						
					}
					else if (benchData < root->benchscore)
					{
						root = root->left;
					}
					else
					{
						root = root->right;
					}
					
					
			}
		
		return -1; //things get here if we couldn't find the data we needed
		
	}
	
}


int displayHostnames(BTREE root, PQUEUE jobs)
{
	LINK tempList = root->serverList;
	
	if (tempList == NULL)
	{
		return -1;
	}
	else
	{
			while(!(tempList == NULL))
			{
				
				printf("TREE NODE VALUE : %d\n HOSTNAME : %s\n",root->benchscore,tempList->hostname);
				tempList = tempList->next;
				
			}
	}
	
}

int launchJobs(BTREE root, PQUEUE jobs)
{
	LINK tempList = root->serverList;
	
	if (tempList == NULL)
	{
		return -1;
	}
	else
	{
		
				int sendVar = SEND_JOB;
				int *sendVarPtr = &sendVar;
				
				int recieveVar = ZERO_OUT_VALUE;
				int *recieveVarPtr = &recieveVar;
				
				int errorTrap = 0;
		while(jobs->numOfElements != 0)
		{		
			//~ (!(tempList == NULL))
			
				//~ SEND_JOB
				
				send(tempList->peerSocket,sendVarPtr,sizeof(int),0);
			
				sendMessage(tempList->peerSocket,jobs->head->value); //this is the command
				
				errorTrap = recv(tempList->peerSocket,recieveVarPtr,sizeof(int),0);
				if (errorTrap < 0)
				{
					
					
				}
				if (recieveVar == RECIEVED_OK)
				{
							if (tempList->next != NULL)
						{
							tempList = tempList->next;
						}
						else
						{
							if (tempList->front != NULL)
							{
								tempList = tempList->front;
							}
						}
						dequeue(jobs);
					
				}
				else
				{
					return -1;
				}
				
			
		}
	}
	
}

int addHostnameToBTree(BTREE root, HOSTNAME hostName, int socket)
{
	if (root == NULL)
	{
		return -1;
	}
	else
	{
		addElementToList(root->serverList,hostName,socket);
	}
}


int doNothing(BTREE root)
{
	sleep(1);
}

int doNothingSearch(BTREE root, HOSTNAME hostName, int socket)
{
	sleep(1);
}
