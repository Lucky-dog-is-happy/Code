#include <iostream>
using namespace std;
int main()
{
    int n, number = 0, temp;
    cin >> n;
    int arr[n];
    temp = n;
    while (temp--)
        cin >> arr[n - temp - 1];
    temp = arr[0];
    for (int i = 0; i < n; i++)
    {

        if (arr[i] < temp)
            temp = arr[i], number = i;
    }
    printf("Minimum value: %d\nPosition: %d", temp, number);
    return 0;
}