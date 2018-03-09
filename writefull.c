#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 20 MiB */
#define WRITE_ONCE 1024*1024*20

int main(void)
{
	FILE *pf = NULL;
	char *lpstr = NULL;
	int ret = 0;

	pf = fopen("a.txt","wb");

	if (!pf)
		exit(1);

	lpstr = (char *)malloc(WRITE_ONCE);
	memset(lpstr, '0', WRITE_ONCE);
	lpstr[WRITE_ONCE - 1] = '\0';

	while(!ret) {
		fprintf(pf, lpstr);
		ret = fflush(pf);
	}
	fclose(pf);

	printf("%d\n", ret);
	system("read -sn1");
	return 0;
}
