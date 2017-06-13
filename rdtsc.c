#include<stdio.h> 
#include<stdlib.h>
#include<linux/types.h>

#define TIMES 0
#define SIZE 1024

__u64 rdtsc()
{
    __u32 lo,hi;

    __asm__ __volatile__
        (
         "rdtsc":"=a"(lo),"=d"(hi)
        );
    return (__u64)hi<<32|lo;
}

int myfunction()
{
    int i;
    char *p = NULL;
    for(i = 0;i<TIMES;i++)
    {
        p = (char*)malloc(SIZE*sizeof(char));
        if(p)
        {
            free(p);
        }
        else
        {
            printf("malloc failed when i = %d\n",i);
        }
    }
    return 0;
}
int test_rdtsc()
{
    __u64 begin;
    __u64 end;

    begin = rdtsc();
    myfunction();
    end = rdtsc();
    printf("myfunction cost %llu CPU cycles\n",end-begin);
    return 0;
}

int main()
{
    test_rdtsc();
    return 0;
}