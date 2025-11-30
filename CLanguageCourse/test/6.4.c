#include <stdio.h>
int main()
{
  int n;
  scanf("%d",&n);
  int array[n][n];
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    scanf("%d",&array[i][j]);
  }
  int x=0, y=0, right=1, none=1;
  for(int i=0;i<n;i++)
  {
    right = 1;
    x = i, y = 0;
    for(int j=0;j<n;j++)
    {
      if(array[i][j]>array[x][y])
      x = i, y = j;
    }
    for(int j=0;j<n;j++)
    {
      if(array[j][y]<array[x][y])
      right = 0;
    }
    if(right) none=0, printf("%d %d",x,y);
  }
  if(none) printf("NONE");
}