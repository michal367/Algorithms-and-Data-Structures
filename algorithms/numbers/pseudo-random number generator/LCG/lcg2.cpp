#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int LCG(int m, int a, int c, int seed)
{
    return (a*seed + c)%m;
}

int NWD(int a, int b)
{
    while(b != 0)
    {
        int temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}

int main()
{
    srand(time(NULL));

    cout << "Pseudo-random number generator - LCG - Linear Congruential Generator" << endl;
    cout << "x_max - max value" << endl
         << "x0 - seed" << endl
         << "k - amount of generated numbers" << endl
         << "a - multiplier" << endl
         << "c - increment" << endl << endl;

    int x_max, x0, k;
    cout << "x_max: ";
    do{
        cin >> x_max;
    }while(x_max <= 0);
    cout << "x0: ";
    do{
        cin >> x0;
    }while(x0 < 0);
    cout << "k: ";
    do{
        cin >> k;
    }while(k <= 0);
    cout << endl;

    int m, a,c;
    m = x_max + 1;
    a = m + 1;
    do{
        c = rand()%m;
    }while(NWD(c,m) != 1);

    cout << "m: " << m << endl
         << "a: " << a << endl
         << "c: " << c << endl << endl;

    int counter = 0;
    int random = x0;
    for(int i=0; i<k; ++i)
    {
        random = LCG(m, a, c, random);
        cout << ++counter << ": " << random << endl;
    }



    cout << endl;
    system("pause");
    return 0;
}

