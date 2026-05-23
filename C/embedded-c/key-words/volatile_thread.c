#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// int wait = 1;
volatile int wait = 1;

void *func(void *arg)
{
    while(1) {
        sleep(1);
        wait = 0;
        printf("wait = %d in thead\n", wait);
    }
    return NULL;
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, NULL, func, NULL);
    while(wait);
    printf("wait = %d in main\n", wait);
    return 0;
}
