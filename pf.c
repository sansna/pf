#include "pf.h"

int pf(char *s, char *buf)
{
    FILE *pF = NULL;
    char name[100];

    snprintf(name, 100, "/home/pf%s", s);
    pF = fopen(name,"w");
    fprintf(pF, "%s", buf);
    fclose(pF);
    return 0;
}
