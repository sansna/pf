/* stack-above-main.c: In this snippet, we change rbp or rsp in function().
 *
 * - When we change rbp, the back trace printed by gdb will be changed, because
 * gdb uses rbp to determing stack. but the whole flow of the function will not
 * be changed, because that is determined by rsp.
 *
 * - When we change rsp, the back trace printed by gdb in function will *not* be
 * changed because gdb uses rbp to determine back trace. But when we returned
 * out of function, we go to the stack which is above main, and thus its rbp is
 * changed to the one above main. Thus the print result will be the stack above
 * main.
 */
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
