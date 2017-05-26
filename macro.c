#include <stdio.h>

/* Normal Usage of multiple args */
#define PRINT(...) printf(__VA_ARGS__)

/* Given name to multiple args */
#define PRINT_ARGS(args...) printf(args)

/*
 * This usage should give at least one arg after format,
 * otherwise it becomes printf(format, ) which is wrong in GNU C,
 * but seems allowed by GNU CPP in the following form.
 */
#define PRINT_WITH_ARG(format, ...) printf(format, __VA_ARGS__)

/* Normal usage of Sharpsharp sample */
#define PS(g, g2) g##g2

/*
 * Special usage of Sharpsharp when placed between a comma and a variable
 * argument. In this case, if the variable argument is left out, then the
 * previous comma will be deleted too.
 */
#define PRINT_SHARPSHARP(format, ...) printf(format, ##__VA_ARGS__)

/* Pound sign: Transform name of arg to (const char*)"arg" */
#define PNAME_AND_VALUE(arg) printf(#arg " = %d\n", arg)

int
main()
{
    int a = 10;
    PRINT("%d\n", a);
    PRINT_ARGS("%d\n", a);

    //PRINT_WITH_ARG("ahhh\n");       //    X
    PRINT_SHARPSHARP("ahhh2\n");     //    O

    /* Usage sample */
    PS(PRINT, _ARGS)("paste\n");
    PNAME_AND_VALUE(a);
}
