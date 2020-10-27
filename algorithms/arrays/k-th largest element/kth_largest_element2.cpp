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

    int* ar_m = new int[k+1];
    for(int i=0; i < k; ++i)
        ar_m[i] = a;
    ar_m[k] = b;


    for(int i=0; i < n; ++i)
    {
        int x = ar[i];
        int j = -1;
        while(x > ar_m[j+1])
        {
            ++j;
            ar_m[j] = ar_m[j+1];
        }
        if(j != -1)
            ar_m[j] = x;
    }

    cout << endl;
    cout << k << "-th largest element is " << ar_m[0] << endl;

    cout << endl << "M array:" << endl;
    for(int i=0; i<k+1; ++i)
        cout << ar_m[i] << " ";



    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}






