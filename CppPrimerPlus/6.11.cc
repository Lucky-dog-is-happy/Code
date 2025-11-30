#include <iostream>
#include <cctype>

using namespace std;

void practice1()
{
    char ch;
    cin >> ch;
    while(ch != '@')
    {
        cin >> ch;
        if(ch >= '0' && ch <= '9') continue;
        if(ch >= 'a' && ch <= 'z') ch = toupper(ch);
        if(ch >= 'A' && ch <= 'Z') ch = tolower(ch);
        cout << ch;
        
    }
}

int main()
{
    practice1();
    return 0;
}