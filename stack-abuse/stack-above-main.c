#include <stdio.h>

int function(int a, int b, int c, int d)
{
	d = a + b + c;
	__asm__ __volatile__(
					 "addq $0x10, %rsp" // move current rsp to main's rsp, 
					);			// which is 2*8 bytes = 0x10 bytes above.
	return d;
}

void main()
{
	function(1,2,3,5); // calling function inserts 2 8bytes: ret & %rbp;
	printf("Hello neversee.\n"); // Statements below are always ignroed.
	return;
}
