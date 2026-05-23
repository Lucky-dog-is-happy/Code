#include <iostream>

using namespace std;

const double PI = 3.14159;

int main()
{
    double A,B,C;
    cin >> A >> B >> C;
    double S1 = 1/2.0 * A * C;
    double S2 = PI * C * C;
    double S3 = (A + B) * C / 2.0;
    double S4 = B * B;
    double S5 = A * B;
    printf("TRIANGULO: %.3lf\n",S1);
    printf("CIRCULO: %.3lf\n", S2);
    printf("TRAPEZIO: %.3lf\n", S3);
    printf("QUADRADO: %.3lf\n", S4);
    printf("RETANGULO: %.3lf\n", S5);
    return 0;
}