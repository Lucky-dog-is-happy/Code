#include <iostream>
#include <cstring>
#include <string>
#include <array>
using namespace std;

// 4.13.1
int practice1()
{
    string firstName;
    
    cout << "What is your first name? ";
    getline(cin, firstName);
    
    char* lastName = new char [5];
    cout << "What is your last name? ";
    cin.getline(lastName, 5); 

    char letter;
    cout << "What letter grade do you deserve? ";
    cin >> letter;

    int age;
    cout << "What is your age? " ;
    cin >> age;

    cout << "Name: " << lastName << ", " << firstName <<endl;
    cout << "Grade: " << letter << endl;
    cout << "age: " << age << endl;
    return 0;
}
// 4.13.3
void practice3()
{
    string first_name, last_name;
    cout << "Enter your first name: ";
    getline(cin, first_name);
    cout << "Enter your last name: ";
    getline(cin, last_name);
    string full_name = last_name + ", " + first_name;
    cout << "Here's the information in a single string: " << full_name << endl;
}
// 4.13.4
void practice4()
{
    char first_name[10], last_name[10];
    cout << "Enter your first name: ";
    cin.getline(first_name, 10);
    cout << "Enter your last name: ";
    cin.getline(last_name, 10);
    char full_name[20];
    strcpy(full_name, last_name);
    strcat(full_name, ", ");
    strcat(full_name, first_name);
    cout << "Here's the information in a single string: " << full_name << endl;
}
// 4.13.5
int practice5()
{
    struct CandyBar
    {
        string brand;
        double weight;
        int calorie;
    };
    CandyBar snack = {"Mocha Munch", 2.3, 350};
    cout << "snack: " << snack.brand << ", " << snack.weight << ", " << snack.calorie << endl;
    return 0;
}
// 4.13.6
int practice6()
{
    struct CandyBar
    {
        string brand;
        double weight;
        int calorie;
    };
    CandyBar array[2] =
        {
            {"awsl", 5.2, 250},
            {"Mocha Munch", 2.3, 350}};
    for (int i = 0; i < 2; i++)
    {
        cout << "array[" << i << "]: " << array[i].brand << ", " << array[i].weight << ", " << array[i].calorie << endl;
    }
    return 0;
}
// 4.13.7
int practice7()
{
    struct pizza
    {
        string company;
        double diameter;
        double weight;
    };
    pizza makabaka;
    getline(cin, makabaka.company);
    cin >> makabaka.diameter >> makabaka.weight;
    cout << makabaka.company << ", " << makabaka.diameter << ", " << makabaka.weight << endl;
}
// 4.13.8
int practice8()
{
    struct pizza
    {
        string company;
        double diameter;
        double weight;
    };
    pizza *makabaka = new pizza;
    cin >> makabaka->diameter;
    cin.get(); //读取换行符！！！
    getline(cin, makabaka->company);
    cin >> makabaka->weight;
    cout << makabaka->company << ", " << makabaka->diameter << ", " << makabaka->weight << endl;
    delete makabaka;
    return 0;
}
// 4.13.9
int practice9()
{
    struct CandyBar
    {
        string brand;
        double weight;
        int calorie;
    };
    CandyBar *xiaobaitu = new CandyBar[3]{
        {"hello", 4.2, 5},
        {"happy", 3.7, 6},
        {"fuck", 52.2, 4}
    };
    // xiaobaitu = [
    //     {"hello", 4.2, 5},
    //     {"happy", 3.7, 6},
    //     {"fuck", 52.2, 4}
    // ]; 这样不行，动态数组不能一次性赋值（但初始化可以）
    for (int i = 0; i < 3; i++)
    {
        cout << "array[" << i << "]: " << xiaobaitu[i].brand << ", " << xiaobaitu[i].weight << ", " << xiaobaitu[i].calorie << endl;
    }
    delete []xiaobaitu;
    return 0;
}
// 4.13.10
int practice10()
{
    array<double,3> arr;
    cin >> arr[0] >> arr[1] >> arr[2];
    cout << "Your average grade is " << (arr[0]+arr[1]+arr[2])/3.0 << "s." << endl;
    return 0;
}

int main()
{
    practice10();
    return 0;
}