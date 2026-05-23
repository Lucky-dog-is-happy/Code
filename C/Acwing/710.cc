#include <iostream>
using namespace std;
int main()
{
    int x;
    cin >> x;
    int count = 0;
    while (count < 6)
    {
        if (x%2==1) count++,cout << x << endl;
        x++;
    }
    return 0;
}