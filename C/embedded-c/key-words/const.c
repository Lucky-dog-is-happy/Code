#include <stdio.h>

int main(void)
{
    // two ways are the same
    const int a = 10;
    int const b = 20;

    int *p = &a;
    // a = 20;
    // can be changed by pointer
    p[1] = 10;

    printf("a = %d, b = %d\n", a,b);
    printf("a = %p, b = %p\n", &a,&b);
    
    const int * message_no_chanegd;
    int const * message_no_changed;
    int * const pointer_no_changed;
    const int * const pointer_and_message_no_changed;

    return 0;
}
