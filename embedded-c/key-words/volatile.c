#include <stdio.h>

volatile unsigned char buff;

int main(void)
{
    while (buff) {
        printf("the message in buff is ---");
    }
    return 0;
}
