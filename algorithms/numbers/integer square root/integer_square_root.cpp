#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
    cout << "Integer square root" << endl;
    cout << "n - number from which the integer square root is to be calculated" << endl << endl;

    int n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);


    int i = 0;
    int square = 0, diff = 1;
    while(square <= n)
    {
        square += diff;
        diff += 2;
        ++i;
    }

    cout << i-1 << endl;


    cout << endl;
    system("pause");
    return 0;
}
