#include <stdio.h>
int reverse(int n)
{
  int negative=0,len=1,start=0,output=0;
  if(n<0) negative = 1,n = -n;
  int temp=n;
  while((temp=temp/10) != 0) len++;
  int array[len];
  for(int i=0;i<len;i++)
  {
    array[i] = n%10;
    n = n/10;
  }
  for(int i=0;i<len;i++)
  {
    if(array[i]!=0) start=1;
    if(start)
    {
      output = 10*output + array[i];
    }
  }
  if(negative) output = -output;
  return output;
}
int main()
{
  int n;
  scanf("%d",&n);
  printf("%d\n",reverse(n));
  return 0;
}