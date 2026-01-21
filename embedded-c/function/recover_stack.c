#include <stdio.h>

unsigned long addr = 0;

void show(void)
{
    int a = 10086;
    int b = 10010;

    asm volatile("movq %rbp, addr(%rip)");
}

int main(int argc, char *argv[])
{
    show();

    int *p = (int *)addr;

    printf("a=%d, b=%d\n", p[-1], p[-2]);
}

