#include<stdio.h> 
#include<stdlib.h>
#include<linux/types.h>

__u64 rdtsc()
{
    __u32 lo,hi;

    __asm__ __volatile__
        (
         "rdtsc":"=a"(lo),"=d"(hi)
        );
    return (__u64)hi<<32|lo;
}

int myfunction(int i)
{
	i *= i;
    return i;
}

int test_rdtsc()
{
    __u64 begin;
    __u64 end;
	__u64 i = 0;
	__u64 TRIES = 3000000000; /* 3G, result convergence */
	int j = 0;

    begin = rdtsc();
	/* Circumvent OOO */
	if (begin) {
		for (; i < TRIES; i ++)
			j += myfunction(i);
	}
	/* Circumvent OOO */
	if (j) /* Unlikely to be 0 */
		end = rdtsc();
    printf("myfunction cost %llu/10000 CPU cycles\n",(end-begin)*10000/TRIES);
    return 0;
}

int main()
{
    test_rdtsc();
    return 0;
}
