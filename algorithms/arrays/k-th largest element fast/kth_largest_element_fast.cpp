#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


size_t quick_select(int* array, size_t index_start, size_t index_end, size_t size, int k)
{
    size_t index_pivot = index_start;
    int pivot = array[index_pivot];

    size_t i = index_start, j = index_end + 1; // it isn't index_start-1, because there is pivot which is skipped
    while(i < j)
    {
        while(array[++i] < pivot);
        while(array[--j] > pivot);
        if(i < j)
        {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    array[index_pivot] = array[j];
    array[j] = pivot;

    if(j == size-k)
        return j;
    else if(j > size-k)
        return quick_select(array, index_start, j-1, size,k);
    else
        return quick_select(array, j+1, index_end, size,k);
}


int main()
{
    srand(time(NULL));
    cout << "k-th largest element - Quick Select" << endl;
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
    cout << "b: ";
    cin >> b;
    cout << "k: ";
    cin >> k;
    cout << endl;

    int* ar = new int[n];
    for(int i=0; i<n; ++i)
        ar[i] = rand() % (b-a+1) + a;

    cout << "Generated array:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;

    size_t index = quick_select(ar, 0, n-1, n, k);

    cout << endl;
    cout << k << "-th largest element is " << ar[index] << endl;


    cout << endl;
    cout << "Partitioned array:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;

    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}








