#include <stdio.h>
int main()
{
  unsigned int a,n,array[32];
  scanf("%u %u",&a,&n);
  int i=0;
  while(i<32)
  {
    array[i] = a % 2;
    a = a / 2;
    i++;
  }
  unsigned int temp;
  while(n--)
  {
    temp = array[0];
    for(int i=0;i<32;i++)
    {
      array[i]=array[i+1];
    }
    array[31] = temp;
  }
  temp = 0;
  int multi = 1;
  for(int i=0;i<32;i++)
  { 
    temp += array[i] * multi;
    multi *= 2; 
  }
  printf("%d",temp);
  return 0;
}