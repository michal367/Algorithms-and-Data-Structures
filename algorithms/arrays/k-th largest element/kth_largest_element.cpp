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

    sort(ar, ar+n);

    cout << "Generated sorted array:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;


    cout << endl;
    if(k <= n)
        cout << k << "-th largest element is " << ar[n-k] << endl;
    else
        cout << k << "-th largest element doesn't exist" << endl;


    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}





