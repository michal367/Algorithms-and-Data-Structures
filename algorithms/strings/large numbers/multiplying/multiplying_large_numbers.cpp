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
    cout << "Multiplying non-negative large string number by non-negative small number" << endl
         << "a - large number" << endl
         << "b - small number" << endl << endl;


    string a;
    long long b;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << endl;


    string result;

    string a2 = a;
    while(b)
    {
        if(b & 1)
            result = add(result, a2);
        a2 = add(a2,a2);

        b >>= 1;
    }


    cout << endl << result << endl;


    cout << endl;
    system("pause");
    return 0;
}





