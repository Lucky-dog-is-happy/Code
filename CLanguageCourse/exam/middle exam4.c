#include <stdio.h>
int main()
{
  int n,temp,right,same;
  int array[5];
  for(int i=12365;i<100000;i++)
  {
    n = i;
    right = 0;
    temp = 10000;
    same = 0;
    for(int j=0;j<5;j++)
    {
      array[j] = n / temp;
      n = n % temp;
      temp /= 10;
    }
    for(int j=0;j<5;j++)
    {
      if(array[j]==0)
      {
        same = 1;
        continue;
      }
      for(int k=j+1;k<5;k++)
      {
        if(array[j]==array[k]) same=1;
      }
    }
    if(same) continue;
    if((array[1]*1+array[0]*10)%2==0) right++;
    if((array[2]*1+array[1]*10+array[0]*100)%3==0) right++;
    if((array[3]*1+array[2]*10+array[1]*100+array[0]*1000)%4==0) right++;
    if((array[4]*1+array[3]*10+array[2]*100+array[1]*1000+array[0]*10000)%5==0) right++;
    if(right == 4) printf("%d\n",i);
  }
  return 0;
}