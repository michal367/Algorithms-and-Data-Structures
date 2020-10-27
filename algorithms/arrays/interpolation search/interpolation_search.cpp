#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Interpolation search" << endl;
    cout << "n - size of an array with random values" << endl
         << "a - min value; b - max value" << endl
         << "x - searched value" << endl << endl;

    size_t n;
    int a,b, x;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);
    cout << "a: ";
    cin >> a;
    cout << "b: " ;
    cin >> b;
    cout << "x: " ;
    cin >> x;
    cout << endl;

    int* ar = new int[n];
    for(int i=0; i<n; ++i)
        ar[i] = rand() % (b-a+1) + a;

    sort(ar, ar+n);

    cout << "Generated sorted array:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;
    cout << endl;

    size_t index, index_start = 0, index_end = n-1;
    bool is_found = false;

    if(ar[index_start] != ar[index_end])
    {
        while((ar[index_start] <= x) && (x <= ar[index_end]))
        {
            index = index_start + ((x - ar[index_start]) * (index_end - index_start) / (ar[index_end] - ar[index_start]));
            if(ar[index] == x)
            {
                is_found = true;
                break;
            }
            else if(x > ar[index])
                index_start = index + 1;
            else
                index_end = index - 1;
        }

        if(is_found)
            cout << "Value found at position " << index << endl;
        else
            cout << "Value not found" << endl;
    }
    else if(ar[index_start] == x)
        cout << "Value found on all positions" << endl;
    else
        cout << "Value not found" << endl;



    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}





