#include <stdio.h>
int main()
{
  int a,b,c,temp;
  int array[9];
  char same;
  for(int i=100;i<334;i++)
  {
    a = i;
    b = 2 * a;
    c = 3 * a;
    temp = 100;
    for(int j=0;j<3;j++)
    {
      array[j] = a / temp;
      a = a % temp;
      temp /= 10; 
    }
    temp = 100;
    for(int j=3;j<6;j++)
    {
      array[j] = b / temp;
      b = b % temp;
      temp /= 10; 
    }
    temp = 100;
    for(int j=6;j<9;j++)
    {
      array[j] = c / temp;
      c = c % temp;
      temp /= 10; 
    }
    same = 0;
    for(int j=0;j<9;j++)
    {
      if(array[j]==0)
      {
        same = 1;
        continue;
      }
      for(int k=j+1;k<9;k++)
      {
        if(array[j]==array[k])
        same = 1;
      }
    }
    if(same) continue;
    else printf("%d %d %d\n",i,i*2,i*3);
  }
}