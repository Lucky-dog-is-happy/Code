#include <iostream>
#include <array>
#include <string>
#include <locale> // 规范编码格式
#include <cstring>

using namespace std;

int practice1()
{
    int a,b,sum = 0;
    scanf("%d %d",&a,&b);
    if (a > b) swap(a,b);
    for (int i = a; i <= b; i++)
    {
        sum += i;
    }
    cout << sum << endl;
    return 0;
}

int practice2()
{
    array<long double, 100> factorials;
    factorials[0] = factorials[1] = 1.0;
    for (long double i = 2.0; i <= 100; i++) factorials[i] = factorials[i-1] * i;
    for (int i = 0; i <= 100; i++) cout << i << "! = " << factorials[i] << endl;
    return 0;
}

int practice3()
{
    int number, sum = 0;
    while (cin >> number)
    {
        sum += number;
        cout << sum << endl;
        if (number == 0) break;
    }
    return 0;
}

int practice4()
{
    double Daphne = 100.0;
    double Cleo = 100.0;
    int year = 0;
    do {
        Daphne += 10.0;
        Cleo *= 1.05;
        year ++;
    }while (Daphne > Cleo);
    cout << year << "years" << " Daphne=" << Daphne << " Cleo=" << Cleo << endl;
    return 0;
}

int practice5()
{
    char* months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"};
    array<int, 12> sales;
    for (int i=0; i<12; i++)
    {
        cout << "sales for "<< months[i] << ": ";
        scanf("%d", &sales[i]);
    }
    cout << endl;
    int sum = 0; 
    for (int i : sales) // 用整型i遍历sales数组
    {
        sum += i;
        cout << "sales for " << months[i] << " are " << sales[i] << endl;
    }
    cout << "total sales are " << sum << endl;
    return 0;
}

int practice6()
{
    int sales[3][12]{0}, sum[3]{0}, total=0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            cout << "the " << i+1 << " year," << " the " << j+1 << " month:";
            scanf("%d", &sales[i][j]);
            // cin >> sales[i][j];
            sum[i] += sales[i][j];
        }
        total += sum[i];
    }
    for(int i=0; i < 3; i++) cout << sum[i] << " ";
    cout << endl << total << endl;
    return 0;
}

typedef struct{
    string producer;
    int produce_year;
} car;
int practice7()
{
    int amount;
    cout << "How many cars do you wish to catalog? ";
    cin >> amount;
    cin.get(); // important
    // dog:'cin' doesn't read \n, which leads to leave \n to be read by 'getline'
    car* arr = new car[amount];
    for (int i = 0; i < amount; i++)
    {
        cout << "Car #" << i+1 << ":" << endl;
        cout << "Please enter the make: ";
        getline(cin, (arr + i)->producer);
        cout << "Please enter the year made:";
        cin >> (arr + i)->produce_year;
        cin.get(); // important
    }
    cout << "Here is your collection:" << endl;
    for(int i=0; i<amount; i++)
    {
        cout << (arr+i)->produce_year << " " << (arr+i)->producer << endl;
    }
    delete [] arr; // remember to free the RAM
    return 0;
}

int practice8()
{
    char word[100];
    int count = 0;
    cout << "Enter words (to stop, type the word done):" << endl;
    while(cin >> word)
    {
        if(!strcmp(word,"done")) break; // 传统c语言要用strcmp比较，相同返回0
        count++;                        // classic C language use 'strcmp' to compare two char array,
    }                                   // if they are the same, return 0
    cout << "You entered a total of " << count << " words.";
    return 0;
}

int practice9()
{
    string word;
    int count = 0;
    cout << "Enter words (to stop, type the word done):" << endl;
    while (cin >> word)
    {
        if (word == "done")
            break;
        count++;
    }
    cout << "You entered a total of " << count << " words.";
    return 0;
}

int practice10()
{
    cout << "Enter number of rows:";
    int row;
    cin >> row;
    for (int i=1; i <= row; i++)
    {
        for (int j = 0; j < row-i; j++) cout << ".";
        for (int k = 0; k < i; k++) cout << "*";
        cout << endl; 
    }
    return 0;
}

int main()
{
    practice10();
    return 0;
}