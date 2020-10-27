#include <iostream>
#include <cstdlib>

using namespace std;

int LCG(int m, int a, int c, int seed)
{
    return (a*seed + c)%m;
}

int main()
{
    cout << "Pseudo-random number generator - LCG - Linear Congruential Generator" << endl;
    cout << "k - amount of generated numbers" << endl << endl;

    int k;
    cout << "k: ";
    do{
        cin >> k;
    }while(k <= 0);
    cout << endl;

    int counter = 0;
    int random = 0;
    for(int i=0; i<k; ++i)
    {
        random = LCG(24, 25, 7, random);
        cout << ++counter << ": " << random << endl;
    }


    cout << endl;
    system("pause");
    return 0;
}
