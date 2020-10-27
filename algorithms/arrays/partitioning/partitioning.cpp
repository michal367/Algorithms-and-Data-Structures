#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Partitioning (pivot is from the middle)" << endl;
    cout << "n - the size of an array with random values" << endl
         << "a - min value; b - max value" << endl << endl;

    size_t n;
    int a,b;
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


    size_t index_start = 0, index_end = n-1;
    size_t index_pivot = (index_start + index_end) / 2;
    size_t i = index_start, j = index_end + 1;
    int pivot = ar[index_pivot];

    while(i < j)
    {
        while(ar[++i] < pivot);
        while(ar[--j] > pivot);
        if(i < j)
        {
            int temp = ar[i];
            ar[i] = ar[j];
            ar[j] = temp;
        }
    }
    ar[index_pivot] = ar[j];
    ar[j] = pivot;

    cout << endl;
    cout << "pivot = " << pivot << endl
         << "start position of the second partition = " << j << endl;
    cout << "Partitioned array:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;

    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}







