#include <stdio.h>
double mypow(double x, int n)
{
  double temp = 1;
  while(n--)
  {
    temp *= x;
  }
  return temp;
}
int main()
{
  double x;
  int n;
  scanf("%lf %d",&x,&n);
  printf("%f\n",mypow(x,n));
  return 0;
}