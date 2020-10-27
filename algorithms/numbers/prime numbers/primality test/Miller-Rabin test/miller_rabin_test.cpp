#include <iostream>
#include <cstdlib>
#include <ctime>

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
    srand(time(NULL));

    cout << "Miller-Rabin test" << endl;
    cout << "Checking if a natural number n is prime with high probability" << endl;
    cout << "p - number of attempts - the more attempts the more accurate the result" << endl << endl;

    ulong n,p;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 2);
    cout << "p: ";
    do{
        cin >> p;
    }while(n <= 0);
    cout << endl;

    if(n == 2)
        cout << "Number 2 is prime" << endl;
    else if(n%2 == 0)
        cout << "Number " << n << " is NOT prime" << endl;
    else
    {
        ulong s = 0;
        ulong d = n-1;
        while((d&1) == 0)
        {
            d = d >> 1;
            ++s;
        }
        cout << n << " = " << "2^" << s << " * " << d << " + 1" << endl << endl;

        bool is_prime = true;

        for(ulong i = 0; i < p; ++i)
        {
            ulong a = rand()%(n-2 -2 +1) + 2;
            ulong ad = power_modulo(a,d, n);
            if(ad != 1 && ad != n-1)
            {
                for(ulong j=1; j <= s; ++j)
                {
                    ad = multiply_modulo(ad,ad, n);
                    if(ad == 1 || ad != n-1)
                    {
                        is_prime = false;
                        break;
                    }
                }
                if(!is_prime)
                    break;
            }
        }

        if(is_prime)
            cout << "Number " << n << " is prime or is with a low probability pseudoprime" << endl;
        else
            cout << "Number " << n << " is NOT prime" << endl;
    }


    cout << endl;
    system("pause");
    return 0;
}
