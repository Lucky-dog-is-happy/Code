#include <stdio.h>

char *func(void)
{
    // 这是指针
    char *s = "hello world";
    // 这是拷贝到栈空间
    char buff[] = "hello world";

    printf("func:%s\n", buff);
    // 局部变量返回会出问题
    // clang恰好不动这个空间，gcc就动了
    // return s; Bingo!
    return buff;
}

void main(void)
{
    char *p = func();
    printf("main:%s\n", p);
}
