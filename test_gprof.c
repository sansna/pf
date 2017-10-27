//test_gprof.c
//gcc -O0 -pg test_gprof.c && ./a.out && gprof a.out gmon.out > gprof.txt
//tested success under gcc 4.8(centos), but failed under gcc 7.2.0(arch).

#include<stdio.h>

void func4(void)
{
    printf("\n Inside func4() \n");
    for(int count=0;count<=0XFFFF;count++);
}

void func3(void)
{
    printf("\n Inside func3() \n");
    for(int count=0;count<=0XFFFFFFF;count++);
}

void func2(void)
{
    printf("\n Inside func2() \n");

    for(int count=0;count<=0XFFF;count++);

    func3();
}

void func1(void)
{
    printf("\n Inside func1() \n");
    for(int count=0;count<=0XFFFFFF;count++);

    func2();
}

int main(void)
{
    printf("\n main() starts...\n");
    for(int count=0;count<=0XFFFFF;count++);

    func1();
    func4();
    printf("\n main() ends...\n");

    return 0;
}
