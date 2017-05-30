#include <stdio.h>
typedef struct st {
    int a;
    int b;
    int c[3];
} pst; //size = 20

int main()
{
    pst a;
    a.a=0;
    pst b;  //&b = &a-20
    b.a=0;
    pst c;  //&c = &b-20
    c.a=0;
    pst d __attribute__((aligned(64))); //&d = &c-64
    d.a=0;
    return 0;
}
