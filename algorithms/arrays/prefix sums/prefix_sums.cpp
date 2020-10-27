#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Prefix sums" << endl;
    cout << "n - size of an array with random values" << endl
         << "a - min value; b - max value" << endl
         << "i - starting index of the sum " << endl
         << "j - ending index of the sum" << endl << endl;

    size_t n, i,j;
    int a,b;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);
    cout << "a: ";
    cin >> a;
    cout << "b: " ;
    cin >> b;
    cout << "i: ";
    cin >> i;
    cout << "j: " ;
    do{
        cin >> j;
    }while(j < i || j >= n);
    cout << endl;

    cout << "Generated array:" << endl;
    int* ar = new int[n];
    for(int i=0; i<n; ++i)
    {
        ar[i] = rand() % (b-a+1) + a;
        cout << i << ": " << ar[i] << endl;
    }


    int* ar_prefix_sum = new int[n+1];
    ar_prefix_sum[0] = 0;
    int prefix_sum = 0;
    for(int i=1; i<n+1; ++i)
    {
        prefix_sum += ar[i-1];
        ar_prefix_sum[i] = prefix_sum;
    }

    cout << endl;
    cout << "Prefix sums:" << endl;
    for(int i=0; i<n+1; ++i)
        cout << i << ": " << ar_prefix_sum[i] << endl;


    cout << endl;

    int sum = ar_prefix_sum[j+1] - ar_prefix_sum[i];
    cout << "Sum from T[" << i << "] to T[" << j << "]: " << sum << endl;



    cout << endl;
    system("pause");
    return 0;
}



