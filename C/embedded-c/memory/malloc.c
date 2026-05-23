#include <stdio.h>
#include <stdlib.h>

int global_inited = 10;
int global_uninited;

int main(void)
{
    int local_var = 20;
    char *str = "Hello";
    static int static_var = 30;
    int *heap_var = (int *)malloc(sizeof(int));

    printf("address of code: %p\n", main);
    printf("address of str: %p\n", str);
    printf("address of global_inited: %p\n", (void *)&global_inited);
    printf("address of static_var: %p\n", (void *)&static_var);
    printf("address of global_uninited: %p\n", (void *)&global_uninited);
    printf("address of heap_var: %p\n", (void *)heap_var);
    printf("address of local_var: %p\n", (void *)&local_var);

    free(heap_var);

    return 0;
}
