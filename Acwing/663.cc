#include <iostream>

using namespace std;

int method1()
{
    int x, y, z;
    cin >> x >> y >> z;
    int a = x, b = y, c = z;
    if (a > b) swap(a,b);
    if (a > c) swap(a,c);
    if (b > c) swap(b,c);
    printf("%d\n%d\n%d\n", a, b, c);
    cout << endl;
    printf("%d\n%d\n%d\n", x, y, z);
    return 0;
}

#include <cstdio>
#include <iostream>
using namespace std;
int method2()
{
    int a, b, c;
    cin >> a >> b >> c;
    int x, y, z;
    x = max(a, max(b, c));
    y = min(a, min(b, c));
    z = a + b + c - x - y;
    cout << y << endl;
    cout << z << endl;
    cout << x << endl;
    cout << endl;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    return 0;
}
