/*Experimenting with defining constansts to self modify functions.. they are in hex! */

#define ZERO_OUT_VALUE 0x0000
#define SEND_HOSTNAME 0x0001
#define SEND_BENCHSCORE 0x0002
#define SEND_QUEUE_NUM 0x0003
#define RECIEVED_OK 0x0004 //this should be very important
#define KILL_PEER 0x0005

#define QUEUE_JOBS 0x0006
#define DISTRIBUTE_SPECIFIER 0x0007
#define DISTRIBUTE_ROUND_ROBIN 0x0008
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
#define CONTINUE_ADDING_TO_QUEUE 0x0013

#define NEW_PEER 0xFFFF


//more work needs to be done here
