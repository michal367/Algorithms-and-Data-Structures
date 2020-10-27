#include <iostream>
#include <cstdlib>

using namespace std;

typedef unsigned long long ulong;

int main()
{
    cout << "Integer square root - binary digit by digit method" << endl;
    cout << "n - number from which the integer square root is to be calculated" << endl << endl;

    int n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);


    int p = 0;
    ulong m = 1ull << 62;

    while(m > n)
        m >>= 2;
    while(m != 0)
    {
        ulong t = p + m;
        if(n >= t)
        {
            n -= t;
            p = t + m;
        }
        p >>= 1;
        m >>= 2;
        cout << "m: " << m << "   p: " << p << "   n: " << n << endl;
    }
    cout << p << endl;


    cout << endl;
    system("pause");
    return 0;
}


