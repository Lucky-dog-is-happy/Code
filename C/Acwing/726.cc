#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int n, x, count=0;
    cin >> n;
    while (n--)
    {
        cin >> x;
        for (int i=2; i<=sqrt(x); i++)
        // 或者 i<=x/i
        {
            if (x%i==0) count++;
            break;
        }
        if (count!=0) printf("%d is not prime\n", x);
        else printf("%d is prime\n", x);
        count=0;
    }
    return 0;
}