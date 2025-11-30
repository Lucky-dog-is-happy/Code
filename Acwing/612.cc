#include <iostream>

using namespace std;

const double PI = 3.14159;

int main()
{
    int R;
    cin >> R;
    double V = 4/3.0 * PI * R*R*R;
    printf("VOLUME = %.3lf", V);
    return 0;

}