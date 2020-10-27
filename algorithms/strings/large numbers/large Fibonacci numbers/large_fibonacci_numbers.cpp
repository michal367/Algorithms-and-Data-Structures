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

    int move = 0;
    for(int i=a.size()-1, j=b.size()-1; max(i,j) >= 0; --i, --j)
    {
        int res = move;
        if(i >= 0)
            res += a[i]-'0';
        if(j >= 0)
            res += b[j]-'0';
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
    cout << "Large Fibonacci numbers" << endl
         << "n - n-th number of Fibonacci sequence" << endl << endl;


    int n;
    cout << "n: ";
    cin >> n;
    cout << endl;


    string x = "0";
    string y = "1";

    if(n >= 1)
        cout << "1: " << x << endl;
    if(n >= 2)
        cout << "2: " << y << endl;

    for(int i=2; i<n; ++i)
    {
        string temp = y;
        y = add(x,y);
        x = temp;
        cout << i+1 << ": " << y << endl;
    }



    cout << endl;
    system("pause");
    return 0;
}

