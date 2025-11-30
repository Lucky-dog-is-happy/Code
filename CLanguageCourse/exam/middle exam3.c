#include <stdio.h>
int main()
{
  int n,temp;
  scanf("%d",&n);
  char arr[10];
  for(int i=1234;i<=(98765/n);i++)
  {
    temp = i;
    for(int j=0;j<5;j++)
    {
      arr[j] = temp % 10;
      temp /= 10;
    }
    temp = i * n;
    for (int j = 5; j < 10; j++)
    {
      arr[j] = temp % 10;
      temp /= 10;
    }
    int same=0;
    for(int j=0;j<10;j++)
    {
      for(int k=j+1;k<10;k++)
      {
        if(arr[j]==arr[k]) same=1;
      }
    }
    if (same==1) continue;
    else
    {
      if(i<10000)
      printf("%d/0%d=%d\n",i*n,i,n);
      else
      printf("%d/%d=%d\n",i*n,i,n);
    }
  }
}