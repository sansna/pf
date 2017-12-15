/* stack-overflow.c: only work in -O0 mode.
 * the %rip manipulation not work
 * in O2 mode.
 *
 * Further improvements (with generated assembly):
 * If need to generate O2-opt code:
 * first generate assembly in O2: gcc -S -O2 stack-overflow.c
 * then modify the assembly: vim stack-overflow.s
 * last gas the assembly to binary: gcc -O0 stack-overflow.s -o stack-overflow.out
 */
#include <stdio.h>

void function(int a, int b, int c)
{
	char buf[7];   // takes 16 bytes
	char buf2[10]; // takes 16 bytes
	int *ret;
	ret = buf + 24; //buf takes 16 bytes, fp takes 8 bytes
	(*ret) += 147;
}

int main()
{
	int x;
	x = 0;
	function(1,2,3); //call: pushes %rip to stack and jmp to function
	x = 1;
	printf("%d\n",x);
	printf("%d\n",x);
	printf("%d\n",x);
	printf("%d\n",x);
	printf("%d\n",x);
	printf("%d\n",x);
	printf("%d\n",x);
	// after function is called, jump directyly here.
	printf("%d\n",x);
	return 0;
}
