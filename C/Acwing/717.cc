#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int arr[n];
    arr[0] = 0;
    arr[1] = arr[2] = 1;
    for (int i=3; i<n; i++) arr[i] = arr[i-1] + arr[i-2];
    for (int i=0; i<n; i++) cout << arr[i] << " ";
    return 0;
}

// 滚动数组解法
int method2()
{
    int n, a=0, b=1, c;
    cin >> n;
    while (n--)
    {
        cout << a << ' ';
        c = a + b;
        a = b;
        b = c;
    }
    return 0;
}