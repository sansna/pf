#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stdout, " Usage: ./perror errno<CR>\n");
        return 0;
    }

    fprintf(stdout, "%s\n", strerror(atoi(argv[1])));
    return 0;
}
