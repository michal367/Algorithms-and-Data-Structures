#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;


size_t quick_select(int* array, size_t index_start, size_t index_end, size_t size, int k)
{
    size_t i = index_start, j = index_end + 1;
    size_t index_pivot = index_start;
    int pivot = array[index_pivot];
    while(i < j)
    {
        while(array[++i] < pivot);
        while(array[--j] > pivot);
        if(i < j)
            swap(array[i], array[j]);
    }
    array[index_pivot] = array[j];
    array[j] = pivot;

    if(j == k)
        return j;
    else if(j < k)
        return quick_select(array, j+1, index_end, size, k);
    else
        return quick_select(array, index_start, j-1, size, k);
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
        median = ar[quick_select(ar, 0, n-1, n, (n-1)/2)];
        cout << "Median: " << median << endl;
    }
    else
    {
        int median_lower = ar[quick_select(ar, 0, n-1, n, (n-1)/2)];
        int median_upper = ar[quick_select(ar, 0, n-1, n, (n-1)/2 + 1)];
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







