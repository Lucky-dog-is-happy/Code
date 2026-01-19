#include <stdio.h>

typedef struct abc {
    int a;
    int b;
    float c;
} abc_t;

typedef int len_t;
typedef unsigned char uint8_t;
#define uint8 unsigned char
typedef void (*func)(void);

func p;

int main(void)
{
    len_t a = 0;
    uint8_t b;
    abc_t c;

    return 0;
}
