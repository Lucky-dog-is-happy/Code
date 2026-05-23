#include <iostream>
using namespace std;
int main()
{
    int n, x, y, count=0;
    cin >> n;
    for (int i=0; i<n; i++)
    {
        cin >> x >> y;
        int start = (x<y?x:y);
        int end = (x<y?y:x);
        for (int j=start+1; j<end; j++)
            if (j%2==1 || j%2==-1) count+=j;
            //(j%2!=0)
            //负数是奇数余数是-1！！！
        printf("%d\n",count);
        count = 0;
    }
    return 0;
}