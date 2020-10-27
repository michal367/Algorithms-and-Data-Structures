#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Adding non-negative large string numbers" << endl
         << "number1 - first number" << endl
         << "number2 - second number" << endl << endl;


    string number1, number2;
    cout << "number1: ";
    cin >> number1;
    cout << "number2: ";
    cin >> number2;
    cout << endl;


    string result;

    int zeros;
    for(zeros=0; number1[zeros] == '0'; ++zeros);
    number1.erase(0,zeros);
    for(zeros=0; number2[zeros] == '0'; ++zeros);
    number2.erase(0,zeros);

    while(number1.size() > number2.size())
        number2 = '0' + number2;
    while(number2.size() > number1.size())
        number1 = '0' + number1;

    int move = 0;
    for(int i=number1.size()-1, j=number2.size()-1; i >= 0; --i, --j)
    {
        int res = number1[i]-'0' + number2[j]-'0' + move;
        move = 0;
        if(res >= 10)
        {
            move = res/10;
            res %= 10;
        }
        result = char(res+'0') + result;
    }
    if(move > 0)
        result = char(move+'0') + result;

    cout << endl << result << endl;


    cout << endl;
    system("pause");
    return 0;
}




