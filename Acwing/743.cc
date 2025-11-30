#include <iostream>
using namespace std;
int main()
{
    const int number = 12;
    double matrix[number][number];
    int l;
    double sum = 0.0;
    char letter;
    cin >> l >> letter;
    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
            cin >> matrix[i][j];
    }
    for (int i = 0; i < number; i++)
        sum += matrix[l][i];
    if (letter == 'S')
        cout << sum;
    else if (letter == 'M')
        printf("%.1lf", sum / 12.0);
    return 0;
}
