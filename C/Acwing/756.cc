// 此题精妙！！！
#include <iostream>
using namespace std;

const int N = 110;
int arr[N][N];

int main()
{
    int r, c;
    cin >> r >> c;

    int left = 0, right = c - 1;
    int top = 0, bottom = r - 1;
    int k = 1;
    while (left <= right || top <= bottom)
    {
        for (int i = left; i <= right && top <= bottom; i++) // 构造最上面一行
        {
            arr[top][i] = k++;
        }
        top++;
        for (int i = top; i <= bottom && left <= right; i++) // 构造最右侧一列
        {
            arr[i][right] = k++;
        }
        right--;
        for (int i = right; i >= left && top <= bottom; i--) // 构造最下面一行
        {
            arr[bottom][i] = k++;
        }
        bottom--;
        for (int i = bottom; i >= top && left <= right; i--) // 构造最左侧一列
        {
            arr[i][left] = k++;
        }
        left++;
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
    return 0;
}
