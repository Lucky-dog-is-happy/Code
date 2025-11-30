#include <iostream>

using namespace std;

int main()
{
    double x, y;
    cin >> x >> y;
    if (x > 0)
    {
        if (y > 0) cout << "Q1";
        if (y < 0) cout << "Q4";
        if (y == 0) cout << "Eixo X";
    }
    else if (x < 0)
    {
        if (y > 0) cout << "Q2";
        if (y < 0) cout << "Q3";
        if (y == 0) cout << "Eixo X";
    }
    else
    {
        if (y == 0) cout << "Origem";
        else cout << "Eixo Y";    
    }
    return 0;
}