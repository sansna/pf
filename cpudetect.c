#include <stdio.h>

int main()
{
	__builtin_cpu_init();

	if (__builtin_cpu_is("corei7"))
	{
	   printf("this is i7,\n");
	}
	else printf("this isnot i7,\n");

	if (__builtin_cpu_is("intel"))
	{
		printf("and this is intel,\n");
	}
	else printf("and this is not intel,\n");

	if (__builtin_cpu_supports("avx2"))
	{
		printf("and supports avx2.\n");
	}
	else printf("and not supports avx2.\n");

	return 0;
}

