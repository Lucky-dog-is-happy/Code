#include <iostream>

using namespace std;
// 3.7.1
int practice1()
{
    int height,meter,cemi;
    cin >> height;
    meter = height / 100;
    cemi = height % 100;
    cout << height << "cm is equal to " << meter << "m and " << cemi << "cm" << endl;
    return 0;
}
// 3.7.3
int practice3()
{
    int degree, minute, second;
    double result;
    cout << "Enter a latitude in degrees, minutes, and seconds:" << endl;
    cout << "First, enter the degrees:__\b\b";
    cin >> degree;
    cout << "Next, enter the minutes of arc:__\b\b";
    cin >> minute;
    cout << "Finally, enter the seconds of arc:__\b\b";
    cin >> second;
    result = degree + minute / 60.0 + second / 3600.0;
    cout << degree << " degrees, " << minute << " minutes, " << second << " seconds = " << result << " degrees." << endl;
    return 0;
}
// 3.7.4
int practice4()
{
    long input;
    int day, hour, minute, second;
    cout << "Enter the number of seconds: ";
    cin >> input;
    minute = input / 60;
    second = input % 60;
    hour = minute / 60;
    minute = minute % 60;
    day = hour / 24;
    hour %= 24;
    cout << input << " seconds = " << day << " days, " << hour << " hours, " << minute << " minutes, " << second << " seconds.";
    return 0;
}

int main()
{
    practice4();
    return 0;
}