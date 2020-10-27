#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void shuffle(int* array, size_t size)
{
    for(int i=0; i < 3*size; ++i)
    {
        size_t r1 = rand() % size;
        size_t r2 = rand() % size;
        int temp = array[r1];
        array[r1] = array[r2];
        array[r2] = temp;
    }
}


int main()
{
    srand(time(NULL));
    cout << "Shuffle array" << endl;
    cout << "n - size of an array with values from 1 to n" << endl << endl;

    size_t n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n <= 0);
    cout << endl;

    int* array = new int[n];
    for(int i=0; i<n; ++i)
        array[i] = i+1;

    shuffle(array, n);

    for(int i=0; i<n; ++i)
        cout << i + 1 << ": " << array[i] << endl;


    cout << endl;
    system("pause");
    return 0;
}
