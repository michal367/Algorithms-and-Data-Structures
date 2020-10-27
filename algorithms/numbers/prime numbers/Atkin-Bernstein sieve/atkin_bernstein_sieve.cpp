#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
    cout << "Atkin-Bernstein sieve" << endl;
    cout << "Prime numbers in a range <2;n> generated by Atkin-Bernstein sieve" << endl << endl;

    int n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n<2);

    const int size = n-4;
    bool* is_prime = new bool[size];
    for(bool* ptr = is_prime; ptr != is_prime+size; ++ptr)
        *(ptr) = false;


    int square_root = sqrt(n);

    for(int x=1; x <= square_root; ++x)
    {
        int x2 = x*x;
        for(int y = 1; y <= square_root; ++y)
        {
            int y2 = y*y;

            int z = 4*x2 + y2;
            if(z <= n && (z%12 == 1 || z%12 == 5))
                *(is_prime + z - 5) = !(*(is_prime + z - 5));

            z -= x2;
            if(z <= n && z%12 == 7)
                *(is_prime + z - 5) = !(*(is_prime + z - 5));

            if(x > y)
            {
                z -= 2*y2;
                if(z <= n && z%12 == 11)
                    *(is_prime + z - 5) = !(*(is_prime + z - 5));
            }
        }
    }
    for(int i = 5; i <= square_root; i++)
        if(*(is_prime + i - 5))
        {
            int x2 = i * i;
            int z = x2;
            while(z <= n)
            {
                *(is_prime + z - 5) = false;
                z += x2;
            }
        }


    cout << endl << "Prime numbers in a range <2;" << n << ">:" << endl;

    int counter = 0;
    if(n >= 2)
        cout << ++counter << ": 2" << endl;
    if(n >= 3)
        cout << ++counter << ": 3" << endl;

    bool* ptr = is_prime;
    for(int i=5; i <= n; ++i, ++ptr)
    {
        if(*ptr)
            cout << ++counter << ": " << i << endl;
    }


    delete[] is_prime;

    cout << endl;
    system("pause");
    return 0;
}
