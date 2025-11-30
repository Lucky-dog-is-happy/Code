#include <iostream>
using namespace std;
int main()
{
    int n, a, animals=0, coneys=0, rats=0, frogs=0;
    char t;
    cin >> n;
    for (int i=0; i<n; i++)
    {
        cin >> a >> t;
        animals += a;
        if (t == 'C') coneys+=a;
        else if (t == 'R') rats+=a;
        else if (t == 'F') frogs+=a;
    }
    printf("Total: %d animals\n", animals);
    printf("Total coneys: %d\n", coneys);
    printf("Total rats: %d\n", rats);
    printf("Total frogs: %d\n", frogs);
    printf("Percentage of coneys: %.2lf %\n", coneys*100.0/animals);
    printf("Percentage of rats: %.2lf %\n", rats * 100.0 / animals);
    printf("Percentage of frogs: %.2lf %\n", frogs * 100.0 / animals);
    return 0;
}