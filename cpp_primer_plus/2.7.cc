#include <iostream>

using namespace std;
// 2.7.1
int practice1()
{
    string name = "lucky dog";
    cout << "My name is " << name << endl;
    return 0;
}
// 2.7.2
int practice2()
{
    int distance;
    cin >> distance;
    cout << distance * 220 << "码" << endl;
    return 0;
}
// 2.7.3
void string1()
{
    cout << "Three blind mice" << endl;
}

void string2()
{
    cout << "See how they run" << endl;
}
int practice3()
{
    string1();
    string1();
    string2();
    string2();
    return 0;
}
// 2.7.4
int practice4()
{
    cout << "Enter your age: " << endl;
    int age;
    cin >> age;
    cout << "You have been living " << age * 12 << " months" << endl;
    return 0;
}
// 2.7.5
double changeCelsiusToFahrenheit(double Celsius)
{
    double Fahrenheit = Celsius * 1.8 + 32.0;
    return Fahrenheit;
}

int practice5()
{
    double Celsius;
    cout << "Please enter a Celsius value: ";
    cin >> Celsius;
    cout << Celsius << "degrees Celsius is " << changeCelsiusToFahrenheit(Celsius) << " degrees Fahrenheit." << endl;
    return 0;
}
// 2.7.6
double lightYearsToAstronomicalUnits(double lightYears)
{
    return 63240 * lightYears;
}

int practice6()
{
    double lightYears;
    cout << "Enter the numer of light years : ";
    cin >> lightYears;
    cout << lightYears
         << " light years = "
         << lightYearsToAstronomicalUnits(lightYears)
         << " astronomical units." << endl;
    return 0;
}
// 2.7.7int main()
int practice7()
{
    int hour, minute;
    cout << "Enter the number of hours: ";
    cin >> hour;
    cout << "Enter the number of minutes: ";
    cin >> minute;
    cout << "Time: " << hour << ":" << minute << endl;
    return 0;
}

int main()
{
    practice7();
    return 0;
}
