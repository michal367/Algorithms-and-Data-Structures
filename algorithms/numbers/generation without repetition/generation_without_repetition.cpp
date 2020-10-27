#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Number generation without repetition" << endl;
    cout << "min - min value" << endl
         << "max - max value" << endl
         << "k - number of generations (k <= (max - min + 1))" << endl << endl;

    int min,max;
    cout << "min: ";
    cin >> min;
    cout << "max: ";
    cin >> max;
    size_t k;
    cout << "k: ";
    do{
        cin >> k;
    }while(k <= 0 || k > (max - min + 1));
    cout << endl;

    int* array = new int[k];


    for(int i=0; i<k; ++i)
    {
        bool is_rep;
        int r;
        do{
            is_rep = false;
            r = rand() % (max-min+1) + min;
            for(int j=0; j<i; ++j)
                if(r == array[j])
                {
                    is_rep = true;
                    break;
                }
        }while(is_rep);
        array[i] = r;
    }


    for(int i=0; i<k; ++i)
        cout << i + 1 << ": " << array[i] << endl;

    delete[] array;

    cout << endl;
    system("pause");
    return 0;
}
