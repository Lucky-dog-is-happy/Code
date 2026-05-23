#include <iostream>

using namespace std;

int main()
{
    int A, B, C, D,foo = 0;
    cin >> A >> B >> C >> D;
    if(B>C) if (D>A) if(C+D>A+B) if(C>0 && D>0) if (A%2==0) foo = 1;
    if (foo == 1) printf("Valores aceitos"); else printf("Valores nao aceitos");
    
    return 0;
}