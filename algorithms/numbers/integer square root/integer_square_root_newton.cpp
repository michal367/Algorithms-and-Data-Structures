#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
    cout << "Integer square root - Newton method" << endl;
    cout << "n - number from which the integer square root is to be calculated" << endl << endl;

    int n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);

    if(n == 0)
        cout << 0 << endl;
    else
    {
        int p = 1, p2 = 1;
        do{
            p = p2;
            p2 = (p + n/p)/2;
        }while(p != p2);
        cout << p << endl;
    }


    cout << endl;
    system("pause");
    return 0;
}

