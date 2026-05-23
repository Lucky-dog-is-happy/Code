#include <iostream>
using namespace std;
int main()
{
    int n;
    while(cin >> n)
    {

        int arr[100][100];
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                arr[i][j]= (i-j>0?(i-j):(j-i))+1;
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        if(n!=0) cout << endl;
    }
    return 0;
}
