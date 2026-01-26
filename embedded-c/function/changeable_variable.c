#include <stdio.h>
#include <stdarg.h>

static void va_func(int n, ...)
{
    va_list ptr;
    va_start(ptr, n);
    while(n--) {
        printf("%d\n", va_arg(ptr, int));
    }
    va_end(ptr);
}

int main(void)
{
    va_func(1, 100);
    va_func(2, 200, 300);

    return 0;
}
