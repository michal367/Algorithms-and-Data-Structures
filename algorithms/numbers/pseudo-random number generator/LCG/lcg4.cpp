#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

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

long long LCG(long long m, long long a, long long c, long long seed)
{
    return (multiply_modulo(a,seed,m) + c)%m;
}
long long random(long long min, long long max, long long& seed)
{
    seed = LCG(34359738368, 3141592653, 2718281829, seed);
    return floor((seed/34359738368.0) * (max-min+1)) + min;
}


int main()
{
    srand(time(NULL));

    cout << "Pseudo-random number generator - LCG - Linear Congruential Generator" << endl;
    cout << "min - min value" << endl
         << "max - max value" << endl
         << "k - amount of generated numbers" << endl << endl;

    int min,max, k;
    cout << "min: ";
    cin >> min;
    cout << "max: ";
    cin >> max;
    cout << "k: ";
    do{
        cin >> k;
    }while(k <= 0);
    cout << endl;


    int counter = 0;
    long long seed = time(NULL);
    for(int i=0; i<k; ++i)
    {
        int r = random(min,max, seed);
        cout << ++counter << ": " << r << endl;
    }


    cout << endl;
    system("pause");
    return 0;
}


