#include <iostream>
using namespace std;
int fail()
{
    int n, x, sum=0;
    cin >> n;
    for (int i=0; i<n; i++)
    {
        cin >> x;
        for (int j=1; j<x; j++)
        {
            if (x%j==0) sum+=j;
        }
        if (sum == x) printf("%d is perfect\n",x);
        else printf("%d is not perfect\n",x);
        sum = 0;
    }
    return 0;
}
//纯数学法
int method1()
{
    int n;
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        if (x==6 || n==28 || n==496 || n==8128 || n==33550336)
            cout << n << " is perfect" << endl;
        else cout << n << " is not perfect" << endl;
    }
    return 0;
}
// 遇到约数需要整除，往开平方处思考
#include <cmath>
int method2()
{
    int n, x, sum=1;
    cin >> n;
    while (n--)
    {
        cin >> x;
        if(x==1) {cout << "1 is not perfect" << endl;continue;}
        for(int i=2; i<sqrt(x); i++)
        {
            if (x%i==0)
            {
                int y = x/i;
                if(y == i) sum +=i;
                else sum+=i+y;
            }
        }
        if (sum == x)
            cout << x << " is perfect" << endl;
        else
            cout << x << " is not perfect" << endl;
        sum = 1;
    }
    return 0;
}

int main()
{
    method2();
}