#include <stdio.h>
int gcd(int x, int y)
{
  while (y != 0)
  {
    int temp=y;
    y = x % y;
    x = temp;
  }
  return x;
}
int main()
{
  int x,y;
  scanf("%d %d",&x,&y);
  printf("%d\n",gcd(x,y));
  return 0;
}