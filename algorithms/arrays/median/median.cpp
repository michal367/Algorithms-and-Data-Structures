#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Median" << endl;
    cout << "n - the size of an array with random values" << endl
         << "a - min value; b - max value" << endl << endl;

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
    cout << endl;

    int* ar = new int[n];
    for(int i=0; i<n; ++i)
        ar[i] = rand() % (b-a+1) + a;

    sort(ar, ar+n);

    cout << "Generated sorted array:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;


    cout << endl;
    float median;
    if(n%2 != 0)
    {
        median = ar[(n-1)/2];
        cout << "Median: " << median << endl;
    }
    else
    {
        int median_lower = ar[(n-1)/2];
        int median_upper = ar[(n-1)/2 + 1];
        median = (median_lower + median_upper) / 2.0;
        cout << "Median: " << median << endl
             << "Lower median: " << median_lower << endl
             << "Upper median: " << median_upper << endl;
    }


    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}






