#include <stdio.h>
int main()
{
  int n, count=1;
  scanf("%d",&n);
  int array[n][n];
  int left=0,right=n-1,top=0,bottom=n-1;
  while(left<=right && top<=bottom)
  {
    for(int i=left;i<right;i++) array[top][i] = count++;
    for(int i=top;i<bottom;i++) array[i][right] = count++;
    for(int i=right;i>left;i--) array[bottom][i] = count++;
    for(int i=bottom;i>top;i--) array[i][left] = count++;
    left++,right--,top++,bottom--;
  } 
  if(n%2 != 0)
  {
    array[n/2][n/2] = count;
  }
  if(n == 1) printf("%d",array[0][0]);
  else
  {
    for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(array[i][j]<10) 
      printf("  %d",array[i][j]);
      else if(array[i][j]<100)
      printf(" %d",array[i][j]);
      else printf("%d",array[i][j]);
    }
    printf("\n");
  }
  }
  
  return 0;
}