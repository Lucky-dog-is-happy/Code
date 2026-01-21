#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

int *generate_array(int n, int L, int R)
{
    int *array = (int *)malloc(sizeof(int) * n);
    srand(time(NULL));
    for(int i=0; i<n; i++) {
        array[i] = rand() % (R-L+1) + L;
    }
    return array;
}

void print_array(int *data, int n)
{
    for(int i=0; i<n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main(void)
{
    int *arr = generate_array(10, 5, 20);
    print_array(arr, 10);
    return 0;
}
