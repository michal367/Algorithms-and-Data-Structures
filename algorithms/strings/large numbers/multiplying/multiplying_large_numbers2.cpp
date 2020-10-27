#include <iostream>
#include <cstdlib>

using namespace std;


string add(string a, string b)
{
    string result;

    int zeros;
    for(zeros=0; a[zeros] == '0'; ++zeros);
    a.erase(0,zeros);
    for(zeros=0; b[zeros] == '0'; ++zeros);
    b.erase(0,zeros);

    while(a.size() > b.size())
        b = '0' + b;
    while(b.size() > a.size())
        a = '0' + a;

    int move = 0;
    for(int i=a.size()-1, j=b.size()-1; i >= 0; --i, --j)
    {
        int res = a[i]-'0' + b[j]-'0' + move;
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
    return result;
}


int main()
{
    cout << "Multiplying non-negative large string numbers" << endl
         << "a - first number" << endl
         << "b - second number" << endl << endl;


    string a, b;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << endl;


    string result;


    for(int i=a.size()-1; i >= 0; --i)
    {
        string result2;
        int move = 0;
        for(int j=b.size()-1; j >= 0; --j)
        {
            int res = (a[i]-'0') * (b[j]-'0') + move;
            move = 0;
            if(res >= 10)
            {
                move = res/10;
                res %= 10;
            }
            result2 = char(res+'0') + result2;
        }
        if(move > 0)
            result2 = char(move+'0') + result2;

        for(int k=i; k < a.size()-1; ++k)
            result2 += '0';

        result = add(result, result2);
    }


    cout << endl << result << endl;


    cout << endl;
    system("pause");
    return 0;
}






