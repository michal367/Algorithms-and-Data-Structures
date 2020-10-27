#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Position of max and min value" << endl;
    cout << "n - the size of an array with random values" << endl
         << "a - min value of random; b - max value of random" << endl << endl;

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
    {
        ar[i] = rand() % (b-a+1) + a;
        cout << i << ": " << ar[i] << endl;
    }


    int max = ar[0], min = ar[0], max_index = 0, min_index = 0;
    for(int i=0; i<n; ++i)
    {
        if(ar[i] > max)
        {
            max = ar[i];
            max_index = i;
        }
        if(ar[i] < min)
        {
            min = ar[i];
            min_index = i;
        }
    }

    cout << endl;
    cout << "Position of max: " << max_index << endl
         << "Position of min: " << min_index << endl;

    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}

