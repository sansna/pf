/*
 * This test is used to show how to prevent strings decrypted by:
 * objdump -j .data -S a.out
 * To actually remove symtab/funcname, use # strip a.out(ELF file).
 * And in this way, nm gives no output..
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
int b=1;
int c=2;
int d;

int add(void);
int add(void)
{
    return 1;
}

int main()
{
    char a[28]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','%','\0'};
    char *tmp = (char *)malloc(12);
    char *hell = (char *)malloc(21);
    char *fmt = (char *)malloc(3);
    fmt[0] = a[26];
    fmt[1] = a[18];
    fmt[2] = a[27];//%s
    tmp[1] = a[2];
    tmp[0] = a[12];
    tmp[2] = a[27];//mc

    /* This seems okay. */
    strcpy(hell, "well");

    fprintf(stdout, fmt, tmp);
    fprintf(stdout, fmt, hell);

    /* The following leaves trace in .rodata section even after strip */
    //fprintf(stdout, "%daksdf",b);
    return 0;
}
