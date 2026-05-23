#include <stdio.h>

void stat(int num, int *sum, int *count, int *max)
{
  int arr[100], temp = num, i=0;
  while(temp != 0)
  {
    arr[i] = temp % 10;
    temp /= 10;
    i++;
  }

  *sum = 0;
  for(int j=0; j<i; j++)
    *sum += arr[j];
  
  *count = 0;
  for(int j=0; j<i; j++)
    if(arr[j] % 2 == 1) (*count)++;

  *max = arr[0];
  for(int j=1; j<i; j++)
    if(arr[j] > *max) *max = arr[j];
}

int main()
{
  int num;
  scanf("%d", &num);
  int sum, count, max;
  stat(num, &sum, &count, &max);
  printf("%d %d %d", sum, count, max);
  return 0;
}