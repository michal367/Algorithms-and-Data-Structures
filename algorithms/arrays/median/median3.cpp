#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

void partit(int* array, size_t index_start, size_t index_end, size_t m_index)
{
    while(index_start < index_end)
    {
        int pivot = array[m_index];
        size_t i = index_start, j = index_end;

        do{
            while(array[i] < pivot)
                ++i;
            while(array[j] > pivot)
                --j;
            if(i <= j)
            {
                swap(array[i], array[j]);
                ++i;
                --j;
            }
        }while(i <= j);
        if(j < m_index)
            index_start = i;
        if(m_index < i)
            index_end = j;
    }
}

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

    cout << "Generated array:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;


    cout << endl;
    float median;
    if(n%2 != 0)
    {
        int m = (n-1)/2;
        partit(ar, 0, n-1, m);
        median = ar[m];
        cout << "Median: " << median << endl;
    }
    else
    {
        int m_lower = (n-1)/2;
        int m_upper = (n-1)/2 + 1;
        partit(ar, 0, n-1, m_lower);
        int median_lower = ar[m_lower];
        partit(ar, 0, n-1, m_upper);
        int median_upper = ar[m_upper];



        median = (median_lower + median_upper) / 2.0;
        cout << "Median: " << median << endl
             << "Lower median: " << median_lower << endl
             << "Upper median: " << median_upper << endl;
    }

    cout << endl;
    cout << "Partitioned array:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;



    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}
