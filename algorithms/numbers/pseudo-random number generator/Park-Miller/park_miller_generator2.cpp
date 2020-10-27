#include <iostream>
#include <cstdlib>

using namespace std;

long long random_Park_Miller(long long seed)
{
    long long n = 2147483647;
    long long g = 16807;
    // (g*seed) % n

    long long l = g * (seed & (65535));
    long h = g * (seed >> 16);
    l += (h & 32767) << 16;
    l += (h >> 15);
    if(l > n)
        l -= n;
    return l;
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
        cout << ++counter << ": " << r % (x_max + 1) << endl;
    }


    cout << endl;
    system("pause");
    return 0;
}




