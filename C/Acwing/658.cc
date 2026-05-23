#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, c;
    cin >> a >> b >> c;
    double d = (b*b -4*a*c);
    if (d < 0 || a ==0) cout << "Impossivel calcular";
    else {
        double delta = sqrt(d);
        double x1 = (-b + delta)/(2 * a);
        double x2 = (-b - delta) / (2 * a);
        printf("R1 = %.5lf\n", x1);
        printf("R2 = %.5lf\n", x2);
    }
    return 0;
}