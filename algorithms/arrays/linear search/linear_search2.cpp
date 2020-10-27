#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Linear search" << endl;
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
    cout << endl;

    int* ar = new int[n];
    for(int i=0; i<n; ++i)
    {
        ar[i] = rand() % (b-a+1) + a;
        cout << i << ": " << ar[i] << endl;
    }

    cout << endl;
    cout << "x: ";
    cin >> x;
    cout << endl;


    bool is_found = false;
    for(int i=0; i<n; ++i)
        if(ar[i] == x)
        {
            is_found = true;
            cout << "Found at position " << i << endl;
        }
    if(!is_found)
        cout << "Not found" << endl;


    cout << endl;
    system("pause");
    return 0;
}

