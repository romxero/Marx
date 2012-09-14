#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> //make sure to build with param -lpthread
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <errno.h>
#include <syslog.h>
#include <string.h> //make sure the string library is here
#include <signal.h>

#include <linux/futex.h>
#include <sys/time.h>
#include <sys/epoll.h>


#define CONSTANT1 .314
#define FFTNUM = 36

calculateFFT(int x, int y, long data[x][y], int numSq)
{
	
	
}

void main()
{
	
	
	
}
