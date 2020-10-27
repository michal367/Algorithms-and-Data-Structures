#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
    cout << "Square root - Babylonian method" << endl;
    cout << "n - natural number" << endl
         << "k - number of repetitions - the more repetitions the more accurate result" << endl << endl;

    int n,k;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);
    cout << "k: ";
    do{
        cin >> k;
    }while(k < 0);
    cout << endl;

    if(n == 0)
        cout << "sqrt(" << n << "): " << 0 << endl;
    else
    {
        double p = 1;
        for(int i=0; i<k; ++i)
            p = (p + n/p)/2;

        cout << "sqrt(" << n << "): " << p << endl;
    }
    cout << endl << "lib sqrt(" << n << "): " << sqrt(n) << endl;

    cout << endl;
    system("pause");
    return 0;
}


