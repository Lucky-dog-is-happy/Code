#include <iostream>
using namespace std;
int main()
{
    const int num=20;
    int arr[num];
    for (int i=num-1; i>=0; i--) cin >> arr[i];
    for (int j=0; j<num; j++) printf("N[%d] = %d\n",j, arr[j]);
    return 0;
}