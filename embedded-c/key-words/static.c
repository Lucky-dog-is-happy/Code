#include <stdio.h>

// 外部引用不到了
static int a = 20;
int func(void)
{
    static int b = 10;
    return ++b;
}

int main(void)
{
    // 好玩，clang和gcc编译顺序不同
    printf("a = %d, func() = %d, func()=%d\n", a, func(), func());
    return 0;
}
