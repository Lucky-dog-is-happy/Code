#include <iostream>

using namespace std;

int main()
{
    int a,b;
    double c,total=0.0;
    cin >> a >> b >> c;
    total += b * c;
    cin >> a >> b >> c;
    total += b * c;
    printf("VALOR A PAGAR: R$ %.2lf",total);
    return 0;
}