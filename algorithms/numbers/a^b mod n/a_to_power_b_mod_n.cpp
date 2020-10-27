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
    cout << "Calculating a^b modulo n" << endl << endl;

    ulong a,b,n;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "n: ";
    cin >> n;
    cout << endl;

    cout << a << "^" << b << " mod " << n << endl;


    ulong result = 1;
    ulong mod = a%n;
    if(b & 1)
        result = (result * mod) % n;
    b = b >> 1;
    while(b != 0)
    {
        mod = multiply_modulo(mod,mod, n);
        if(b & 1)
            result = multiply_modulo(result,mod, n);
        b = b >> 1;
        //cout << result << endl;
    }

    cout << "Result: " << result << endl;


    cout << endl;
    system("pause");
    return 0;
}

