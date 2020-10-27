#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Selection sort" << endl;
    cout << "n - size of an array with random values" << endl
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
    cout << "Generated array:" << endl;
    for(int i=0; i<n; ++i)
    {
        ar[i] = rand() % (b-a+1) + a;
        cout << i << ": " << ar[i] << endl;
    }


    int min_index = 0;
    for(int cur_index = 0; cur_index < n-1; ++cur_index)
    {
        int min = b;
        for(int i=cur_index; i<n; ++i)
        {
            if(ar[i] < min)
            {
                min = ar[i];
                min_index = i;
            }
        }
        swap(ar[cur_index], ar[min_index]);
    }

    cout << endl << "Sorted:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;


    cout << endl;
    system("pause");
    return 0;
}

