/*
 * stacksizelimit.c: 
 * Note that normal linux/windows 64bit has a default stack maximum size of 8/1MB.
 * In linux, this size can be changed by: ulimit -s unlimited/size. In windows, this
 * can be changed in a .def module definition file stating STACKSIZE (rounds up to
 * the nearest 64KB.
 */
#include <stdio.h>

int main()
{
	int a[4095*256*1024];
	int b[8192];
	a[0] = 1;
	return 0;
}
