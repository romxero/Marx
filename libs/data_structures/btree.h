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

typedef struct node NODE; //typedef for the node
typedef NODE *BTREE; //typedef for node pointer
// Take this or leave this


BTREE newNode()
{
	//allocates new node data
	return calloc(1, sizeof(NODE));
}

void bTreeInit(BTREE root, DATA passedValue, HOSTNAME hostnameForServerList, int socket)
{
	//initializes the binary tree
			//~ root = newNode();
			root->benchscore = passedValue;
			root->left = NULL;
			root->right = NULL;
			root->serverList = returnListElement();
			
			initLinkedList(root->serverList, hostnameForServerList, socket);
	
}


void releaseBTreeData(BTREE root)
{	
	//deprecated
	free(root->serverList); //release 
	free(root); //free
}

int freeMemInBTree(BTREE root)
{
	//this function is used to free the memory in the binary tree
	removeAllNodes(root->serverList); //removes servers in linked list
	
	free(root);
}


void traverseBTree(BTREE root, const char DIRECTIVE, PQUEUE jobs, int (*functionPointer)(BTREE root, PQUEUE jobs))
{
		//this function traverses a binary tree in three different orders and uses a function pointer to do processes on nodes
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
	//this function adds a node to btree
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
	//this function will search the btree for a specified benchmark score or node (not currently used!)
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
	//used to dispay the host names
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
	//this is used to launch jobs
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
	//this adds a hostname to the binary tree
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
	//just sleeps
	sleep(1);
}

int doNothingSearch(BTREE root, HOSTNAME hostName, int socket)
{
	//just sleeps
	sleep(1);
}



int roundRobinLaunchJobs(BTREE root, PQUEUE jobs)
{
	//this is used to launch jobs
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
				
				
			while(tempList != NULL)
			{
				
				send(tempList->peerSocket,sendVarPtr,sizeof(int),0);
			
				sendMessage(tempList->peerSocket,jobs->head->value); //this is the command
				
				errorTrap = recv(tempList->peerSocket,recieveVarPtr,sizeof(int),0);
				if (errorTrap < 0)
				{
				//do nothing	
					
				}
				
				if (recieveVar == RECIEVED_OK) //everything recieved ok
				{
					
					
						dequeue(jobs); //dequeue the job off of the queue
						
						tempList = tempList->next; //goto next server
					
				}
				
				
				
			}
			
			
	}
			
			return 1; //if things made it here then everything is ok
			
}


int writeDataToRamDisk(BTREE root, PQUEUE jobs)
{
	//used to dispay the host names
	LINK tempList = root->serverList;
	char buffer[128]; //this buffer is to write strings to the output
	int len = 0;
	if (tempList == NULL)
	{
		return -1; //there is nothing in the list
	}
	else
	{
		ramDiskFileHandle = fopen(ramDiskFile, "a"); //open the file
		
		
			while(tempList != NULL)
			{
				
				len = sprintf(buffer, "Benchmark Value : %d\n Hostname : %s\n",root->benchscore,tempList->hostname);
				buffer[len] += '\0'; // add the terminating character
				fputs(buffer,ramDiskFileHandle); //write lines to the file
				tempList = tempList->next; //go forware in the list
				
			}
			
				
				
				fclose(ramDiskFileHandle); //close the file handle
	}
	
}
