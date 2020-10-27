#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Majority element - element that appears more than n/2 times" << endl;
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
    cout << "Generated array:" << endl;
    for(int i=0; i<n; ++i)
    {
        ar[i] = rand() % (b-a+1) + a;
        cout << i << ": " << ar[i] << endl;
    }


    int counter = 0;
    int number;
    for(int i=0; i < n; ++i)
    {
        if(counter == 0)
        {
            number = ar[i];
            ++counter;
        }
        else
        {
            if(ar[i] != number)
                --counter;
            else
                ++counter;
        }
    }

    cout << endl;
    if(counter > 0)
    {
        int counter2 = 0;
        for(int i=0; i<n; ++i)
            if(ar[i] == number)
                ++counter2;

        if(2*counter2 > n) // counter2 > n/2
            cout << "Majority element is " << number << endl
                 << "Appears " << counter2 << " times" << endl;
        else
            cout << "No majority element" << endl;
    }
    else
        cout << "No majority element" << endl;


    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}



