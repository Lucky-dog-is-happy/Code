#include <stdio.h>

// 少用extern
extern "C" void func(void);

int main(void)
{
    func();
    return 0;
}
