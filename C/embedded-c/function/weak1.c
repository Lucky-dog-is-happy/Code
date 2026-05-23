#include <stdio.h>

void __attribute__((weak)) config(void)
{
    printf("config default\n");
}

int main(void)
{
    config();
    return 0;
}
