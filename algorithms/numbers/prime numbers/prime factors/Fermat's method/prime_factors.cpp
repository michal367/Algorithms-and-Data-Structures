#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void prime_factor_Fermat(unsigned long long n)
{
    unsigned long long x = ceil(sqrt(n));
    unsigned long long y;
    do{
        double yd = sqrt(x*x - n);
        y = (unsigned long long)yd;
        if(yd == y)
        {
            unsigned long long m1 = x+y;
            unsigned long long m2 = x-y;

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
        ++x;
    }while(x + y < n);
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
