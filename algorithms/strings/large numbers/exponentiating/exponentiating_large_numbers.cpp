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

string multiply(string a, string b)
{
    string result;
    string z;
    for(int i=b.size()-1; i >= 0; --i)
    {
        string result2;

        string a2 = a;
        int b_digit = b[i]-'0';

        while(b_digit)
        {
            if(b_digit & 1)
                result2 = add(result2, a2);
            a2 = add(a2,a2);

            b_digit >>= 1;
        }
        result2 += z;
        result = add(result, result2);
        z += '0';
    }
    return result;
}

int main()
{
    cout << "Exponentiating non-negative large string number to the non-negative small number" << endl
         << "a - large number" << endl
         << "b - small number" << endl << endl;


    string a;
    long long b;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << endl;


    string result = "1";
    string a2 = a;
    while(b)
    {
        if(b & 1)
            result = multiply(result, a2);
        a2 = multiply(a2,a2);

        b >>= 1;
    }


    cout << endl << result << endl;


    cout << endl;
    system("pause");
    return 0;
}


