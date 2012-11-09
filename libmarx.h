/* This is the main library file for the Marx application
 * 
 * 
 * 
 * 
 * */ 
 
 


/*Experimenting with defining constansts to self modify functions.. they are in hex! */

#define ZERO_OUT_VALUE 0x0000

#define SEND_HOSTNAME 0x0001
#define SEND_BENCHSCORE 0x0002
#define SEND_PRIORITY_NUM 0x0003
#define RECIEVED_OK 0x0004 //this should be very important
#define KILL_PEER 0x0005

#define QUEUE_JOBS 0x0006
#define SEND_DIRECTIVE 0x0007
#define ROUND_ROBIN 0x0008
#define SPECIFIC_PEERS 0x0009
#define MIN 0x000A
#define MAX 0x000B
#define QUEUE_JOBS_END 0x000C

#define SEND_JOB 0x000D
#define SEND_JOB_UNAME 0x000E
#define JOB_RECIEVED_OK 0x000F

#define JOB_RECIEVED_ERROR 0x0010
#define KILL_SERVER 0x0011
#define READY_FOR_JOBS 0x0012

#define RECIEVED_ERROR 0x0013

//~ #define CONTINUE_ADDING_TO_QUEUE 0x0014
//~ #define CONTINUE_ADDING_TO_QUEUE 0x0015
//~ #define CONTINUE_ADDING_TO_QUEUE 0x0016
//~ #define CONTINUE_ADDING_TO_QUEUE 0x0017
//~ #define CONTINUE_ADDING_TO_QUEUE 0x0018
//~ #define CONTINUE_ADDING_TO_QUEUE 0x0019

#define NEW_PEER 0xFFFF

/* Function Prototypes */

/* Socket Stuff */
static int createAndBindSocket(char const *port);

static int make_socket_non_blocking (int sfd);

int sendMessage(int sockfd,char const *message);

char* recieveMessage(int sockfd);

int serverFunction(int socket, BTREE *root, struct priorityQueueContainer *jobQueue, char *loopVar);

int peerFunction(int socket, char *loopVar);

/* ETC Functions */

/* Data structure stuff */

//priority queue
pQueue returnPQueueMem();

void initializePQueue(struct priorityQueueContainer *root);

int pEnqueue(struct priorityQueueContainer *root, QUEUE *passedQueue);

int isPQueueEmpty(struct priorityQueueContainer *root);

int pDequeue(struct priorityQueueContainer *root);

PQUEUE returnPQueueElement();

void heartBeatProcess(struct priorityQueueContainer *root);

//linked lists
int removeAllNodes(LINK root);

void addElementToList(LINK root, HOSTNAME var, int socket);

LINK returnListElement();

void initLinkedList(LINK root, HOSTNAME var, int socket);
/* Config file stuff */

void defaultTheConfigFileData(struct configurationFile *config);

int processConfigFile(struct configurationFile *config, char const *filePath);

/* Include files below */


#include "constant_definitions.h" //this is used for self modifying code and other things
#include "configFile.h" //for the configuration file


#include "data_structures/queue.h" //will only be using the queue library
#include "data_structures/pqueue.h" //priority queue stufff
#include "data_structures/btree.h" //binary tree stuff

#include "etc_functions.h" // misc functions
#include "benchmark.h"
#include "socketConnections.h"