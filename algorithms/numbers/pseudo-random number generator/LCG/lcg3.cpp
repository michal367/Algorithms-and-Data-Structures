#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int LCG(int m, int a, int c, int seed)
{
    return (a*seed + c)%m;
}

int main()
{
    srand(time(NULL));

    cout << "Pseudo-random number generator - LCG - Linear Congruential Generator" << endl;
    cout << "Test whether generator generates all number from 0 to x_max" << endl;
    cout << "x_max - max value" << endl
         << "x0 - seed" << endl
         << "a - multiplier" << endl
         << "c - increment" << endl << endl;

    int x_max, x0,a,c, k;
    cout << "x_max: ";
    do{
        cin >> x_max;
    }while(x_max <= 0);
    cout << "x0: ";
    do{
        cin >> x0;
    }while(x0 < 0);
    cout << "a: ";
    do{
        cin >> a;
    }while(a <= 0);
    cout << "c: ";
    do{
        cin >> c;
    }while(c <= 0);
    cout << endl;


    int counter = 0;
    int m = x_max+1;
    int random = x0;
    bool* values = new bool[m];
    for(int i=0; i<m; ++i)
        values[i] = false;

    for(int i=0; i<m; ++i)
    {
        random = LCG(m, a, c, random);
        values[random] = true;
        cout << ++counter << ": " << random << endl;
    }

    cout << endl;
    bool is_good = true;
    for(int i=0; i<m; ++i)
    {
        if(values[i] == false)
        {
            is_good = false;
            break;
        }
    }
    if(is_good)
        cout << "Correct" << endl;
    else
        cout << "Incorrect" << endl;

    delete[] values;

    cout << endl;
    system("pause");
    return 0;
}

