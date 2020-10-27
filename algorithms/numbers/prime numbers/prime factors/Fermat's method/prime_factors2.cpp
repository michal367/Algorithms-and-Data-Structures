#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void prime_factor_Fermat(unsigned long long n)
{
    unsigned long long x = ceil(sqrt(n));
    unsigned long long dx = 2*x+1;
    unsigned long long dy = 1;
    double e = x*x - n;
    //cout << "e: " << e << endl;

    while(e != 0)
    {
        while(e > 0)
        {
            e -= dy;
            dy += 2;
        }
        while(e < 0)
        {
            e += dx;
            dx += 2;
        }
        if((dx + dy)/2 > n)
        {
            dx = 2;
            dy = 0;
            break;
        }
    }
    unsigned long long m1 = (dx+dy)/2 - 1;
    unsigned long long m2 = (dx-dy)/2;
    if(m2 == 1)
    {
        cout << n << endl;
        return;
    }
    else
    {
        prime_factor_Fermat(m1);
        prime_factor_Fermat(m2);
        return;
    }
}

int main()
{
    cout << "Prime factors - Fermat's method" << endl;
    cout << "Decomposition of the number n into prime factors" << endl << endl;

    unsigned long long n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 2);


    cout << endl << "Prime factors:" << endl;
    unsigned long long m = n;
    while(m%2 == 0)
    {
        m /= 2;
        cout << 2 << endl;
    }

    if(m > 1)
        prime_factor_Fermat(m);


    cout << endl;
    system("pause");
    return 0;
}

