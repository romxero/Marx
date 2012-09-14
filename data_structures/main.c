#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "btree.h"
#define VARIANCE 500

void main()
{
			
			char *string = getenv("HOSTNAME");
			int (*fp)(); //function pointer
			BTREE rootNode = newNode(); //
			int errorTrap = 0;
			bTreeInit(rootNode, 1000, string);
			fp = &addHostnameToBTree; //add function pointer
			searchBtree(rootNode,1000,string,VARIANCE,fp);
			searchBtree(rootNode,1000,"Ryan",VARIANCE,fp);
			searchBtree(rootNode,500,"Calvin",VARIANCE,fp);
			
			
			errorTrap = searchBtree(rootNode,5,"Darla",VARIANCE,fp);
			
			if(errorTrap < 0)
			{
				addToTree(rootNode,5,"Kevin");
			}
			searchBtree(rootNode,5,"Steve",VARIANCE,fp);
			
			//~ printf("%d\n",rootNode->benchscore);
			//~ puts(rootNode->serverList->hostname);
			
			
			fp = &displayHostnames; //display the names of stuff
			
			//~ (*fp)("%s\n",rootNode->serverList->hostname);
			traverseBTree(rootNode,INORDER,fp);
			
			
			fp = &freeMemInBTree; //remove all elements
			
			traverseBTree(rootNode,POST_ORDER,fp);
			
			//~ free(fp);
			//~ free(rootNode);
			//~ releaseBTreeData(rootNode); //releases the data

}
