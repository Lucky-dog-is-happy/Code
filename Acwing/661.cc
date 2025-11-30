#include <iostream>

using namespace std;

int main()
{
    double arr[4], media;
    for (int i=0; i<4; i++) cin >> arr[i];
    int weight[4] = {2,3,4,1};
    for (int i=0; i<4; i++) media += arr[i]*weight[i];
    int weight_total = 0;
    for (int i=0; i<4; i++) weight_total += weight[i];
    media /= weight_total;
    printf("Media: %.1lf\n", media);
    if (media >= 7.0) cout << "Aluno aprovado.";
    else if (media < 5.0) cout << "Aluno reprovado.";
    else
    {
        cout << "Aluno em exame.\n";
        double Y;
        cin >> Y;
        printf("Nota do exame: %.1lf\n", Y);
        media = (media + Y) / 2.0;
        if (media >= 5.0) cout << "Aluno aprovado.\n";
        else cout << "Aluno reprovado.\n";
        printf("Media final: %.1lf", media);
    }
    return 0;
}