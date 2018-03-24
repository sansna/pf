/* stack-abuse.c: only work in -O0 mode.
 * the %rip manipulation not work
 * in O2 mode.
 * And to note in ubuntu version later than 6.10,
 * the -fstack-protector is enabled default. Thus
 * if need to compile on ubuntu, the *-fno-stack-protector*
 * should be specified.
 *
 * Further improvements (with generated assembly):
 * If need to generate O2-opt code:
 * first generate assembly in O2: gcc -S -O2 stack-abuse.c
 * then modify the assembly: vim stack-abuse.s
 * last gas the assembly to binary: gcc -O0 stack-abuse.s -o stack-abuse.out
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
