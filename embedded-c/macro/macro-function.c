#include <stdio.h>

#define FUNC(a,b) do {( (a) = (a) * (b) ); ( a++ );} while(0)

int a = 10;
int main(int agrc, char **argv)
{
	if(0)
		FUNC(a,10);
	else
		FUNC(a,5);
	printf("a is %d \n", a);
	return 0;
}
