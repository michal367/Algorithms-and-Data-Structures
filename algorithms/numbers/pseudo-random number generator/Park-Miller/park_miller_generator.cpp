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

long long random_Park_Miller(long long seed)
{
    return (multiply_modulo(16807,seed, 2147483647 )) % 2147483647;
}


int main()
{
    cout << "Park-Miller pseudo-random number generator" << endl;
    cout << "x_max - max value" << endl
         << "x0 - seed - x0 >= 1 (multiplicative generator)" << endl
         << "k - amount of numbers to generate" << endl << endl;

    int x_max,x0, k;
    cout << "x_max: ";
    cin >> x_max;
    cout << "x0: ";
    do{
        cin >> x0;
    }while(x0 <= 0);
    cout << "k: ";
    do{
        cin >> k;
    }while(k <= 0);
    cout << endl;


    int counter = 0;
    long long r = x0;
    for(int i=0; i<k; ++i)
    {
        r = random_Park_Miller(r);
        cout << ++counter << ": " << r%(x_max+1) << endl;
    }


    cout << endl;
    system("pause");
    return 0;
}



