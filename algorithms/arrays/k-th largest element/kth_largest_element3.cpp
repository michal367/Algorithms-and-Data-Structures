#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "k-th largest element" << endl;
    cout << "n - size of an array with random values" << endl
         << "a - min value; b - max value" << endl
         << "k - which largest element" << endl << endl;

    size_t n;
    int a,b, k;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);
    cout << "a: ";
    cin >> a;
    cout << "b: " ;
    cin >> b;
    cout << "k: " ;
    cin >> k;
    cout << endl;

    int* ar = new int[n];
    for(int i=0; i<n; ++i)
        ar[i] = rand() % (b-a+1) + a;

    cout << "Generated array:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;

    int* ar_counters = new int[b-a+1];
    for(int i=0; i < b-a+1; ++i)
        ar_counters[i] = 0;

    for(int i=0; i < n; ++i)
        ++ar_counters[ar[i]-a];

    int k2 = k;
    for(int i=b-a; i>=0; --i)
    {
        k2 -= ar_counters[i];
        if(k2 <= 0)
        {
            cout << endl;
            cout << k << "-th largest element is " << i+a << endl;
            break;
        }
    }



    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}

