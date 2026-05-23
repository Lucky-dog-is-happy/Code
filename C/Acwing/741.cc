#include <iostream>
using namespace std;
int main()
{
    int t, n;
    long arr[100]{0};
    arr[1]=1;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i=2; i<=n;i++){
            arr[i] = arr[i-1] + arr[i-2];
        } 
        printf("Fib(%d) = %ld\n", n, arr[n]);
    }
    return 0;
}