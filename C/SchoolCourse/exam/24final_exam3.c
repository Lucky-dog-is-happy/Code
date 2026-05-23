#include <stdio.h>

int count(int n)
{
  if(n==1) return 2;
  if(n==2) return 3;
  if(n==3) return 4;
  if(n > 3) return count(n-1) + count(n-3); 
}

int main()
{
  int n=1, m;
  scanf("%d", &m);
  while(count(n++) < m);
  printf("%d", n-1);
  return 0;
}