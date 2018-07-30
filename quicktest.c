#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *a = (char *)malloc(1);
    char *b = (char *)malloc(1);
    char *c = (char *)malloc(b-a);
    char *d = (char *)malloc(1);
    char *e = (char *)malloc(d-c);
    char *f = (char *)malloc(1);
    printf( "    short int: %d\n" , sizeof(short int) ) ;
    printf( "          int: %d\n" , sizeof(int) ) ;
	printf( "     unsigned: %d\n" , sizeof(unsigned) ) ;
	printf( "         long: %d\n" , sizeof(long) ) ;
    printf( "     long int: %d\n", sizeof(long int) ) ;
    printf( "long long int: %d\n", sizeof(long long int) ) ;
    printf( "       size_t: %d\n", sizeof(size_t) ) ;
    printf( "        void*: %d\n", sizeof(void *) ) ;
    printf( "        float: %d\n", sizeof(float) ) ;
    printf( "       double: %d\n", sizeof(double) ) ;
    printf( "  long double: %d\n\n", sizeof(long double) ) ;

    fprintf(stdout, "System malloc uses %d..%d..%d.. alignment.\n",
            b - a,
            d - c,
            f - e);
    fprintf(stdout, "The paging size is %d bytes.\n\n", getpagesize());

    printf( "PRIu32 usage (see source): %"PRIu32"\n\n" , (uint32_t) 42 ) ;
    printf( "__WORDSIZE(fastest size)= %d\n", __WORDSIZE);

    return 0;
}
