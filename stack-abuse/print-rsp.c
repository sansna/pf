#include <stdio.h>

int get_rsp()
{
	__asm__("movq %rsp, %rax");
}

void main()
{
	printf("0x%lx\n",get_rsp());
}
