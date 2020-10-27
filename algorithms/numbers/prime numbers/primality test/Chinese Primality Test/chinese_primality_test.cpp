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

ulong power_modulo(ulong a, ulong e, ulong n)
{
    ulong product = 1;
    ulong mod = a%n;
    if(e & 1)
        product = (product * mod) % n;
    e = e >> 1;
    while(e != 0)
    {
        mod = multiply_modulo(mod,mod, n);
        if(e & 1)
            product = multiply_modulo(product,mod, n);
        e = e >> 1;
    }
    return product;
}

int main()
{
    cout << "Chinese Primality Test" << endl;
    cout << "Checking if a natural number n is prime. (~99,998% correct)" << endl << endl;

    ulong n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 2);
    cout << endl;

    if(n == 2)
        cout << "Number 2 is prime" << endl;
    else
    {
        if(power_modulo(2, n, n) == 2)
            cout << "Number " << n << " has ~99.998% chance to be prime" << endl;
        else
            cout << "Number " << n << " is NOT prime" << endl;
    }

    cout << endl;
    system("pause");
    return 0;
}


