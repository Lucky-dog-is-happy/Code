#include <stdio.h>

int main()
{
    register char a = 1;

    printf("a = %d, addr of a:%p", a, &a);
    return 0;
}
