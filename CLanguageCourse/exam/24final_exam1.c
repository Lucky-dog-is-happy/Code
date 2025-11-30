#include <stdio.h>
#include <math.h>

double func(int A[], int n)
{
  int i;
  double sum=0, avg;
  for(i=0; i<n; i++)
    sum += A[i];
  avg = sum*1.0 / n;
  sum = 0;
  for(i=0; i<n; i++)
    sum += (A[i] - avg) * (A[i] - avg);
  return sqrt(sum*1.0 / n);
}

int main()
{
  int n, i;
  scanf("%d",&n);
  int A[n];
  for(i = 0; i<n; i++)
    scanf("%d", &A[i]);
  printf("%.5lf",func(A, n));
  return 0;
}