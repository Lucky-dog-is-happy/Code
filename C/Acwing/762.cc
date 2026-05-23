#include <iostream>
using namespace std;
int main()
{
    const int length=110;
    char a[length], b[length];
    double k;
    int count = 0, num = 0;
    cin >> k;
    getchar();
    cin.getline(a,length);
    cin.getline(b,length);
    for (int i = 0; a[i]!='\0'; i++)
    {
        if (a[i]==b[i]) count++;
        num++;
        cout << a[i] << ' ' << b[i] << endl;
    }
    if (count / (double)num >= k) cout << "yes";
    else cout << "no";
    cout << count << endl << num << endl;
    cout << count / (double)num;
    return 0;
}