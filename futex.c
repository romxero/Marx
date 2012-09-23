//~ #include <linux/futex.h>
#include <linux/futex.h>

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

	//futex
       //~ int futex(int *uaddr, int op, int val, const struct timespec *timeout,
                 //~ int *uaddr2, int val3);


void main()
{
	
	int *addr; 
	int errorTrap = futex(NULL,NULL,NULL,NULL,NULL,NULL); // try this out
//	 syscall(SYS_futex , &futex_var, FUTEX_WAKE, 1, NULL, NULL, NULL);
	//this is a system call right here
	//try this out
	
}
