#include <iostream>
#include <cstdlib>

using namespace std;

typedef unsigned long long ulong;

ulong multiply_modulo(ulong a, ulong b, ulong n)
{
    ulong sum = 0;
    while(b != 0)
    {
        if(b & 1)
            sum = (sum + a) % n;
        a = (2*a) % n;
        b = b >> 1;
    }
    return sum;
}

int main()
{
    cout << "Calculating a x b modulo n" << endl << endl;

    ulong a,b,n;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "n: ";
    cin >> n;
    cout << endl;

    cout << multiply_modulo(a,b, n) << endl;

    cout << endl;
    system("pause");
    return 0;
}
