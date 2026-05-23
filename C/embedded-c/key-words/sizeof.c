#include <stdio.h>

// sizeof 不是函数哦
int a=10;
int b=0;
int c=0;

// 编译时候已经算好了，不会调用
int my_sizeof(int x)
{
	return sizeof(x);
}

int main(int argc, char **argv)
{
	int a = 10;

	printf("sizeof = %ld \n", sizeof(my_sizeof(a)));
	b = sizeof a;
	c = my_sizeof(a);
	return 0;
}
