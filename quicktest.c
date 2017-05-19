#include <inttypes.h>
#include <stdio.h>

int main() {
  printf( "    short int: %d\n" , sizeof(short int) ) ;
  printf( "          int: %d\n" , sizeof(int) ) ;
  printf( "     long int: %d\n", sizeof(long int) ) ;
  printf( "long long int: %d\n", sizeof(long long int) ) ;
  printf( "       size_t: %d\n", sizeof(size_t) ) ;
  printf( "        void*: %d\n", sizeof(void *) ) ;
  printf( "        float: %d\n", sizeof(float) ) ;
  printf( "       double: %d\n", sizeof(double) ) ;
  printf( "  long double: %d\n\n", sizeof(long double) ) ;


  printf( "PRIu32 usage (see source): %"PRIu32"\n\n" , (uint32_t) 42 ) ;
  printf( "__WORDSIZE(fastest size)= %d\n", __WORDSIZE);
  return 0;
}
