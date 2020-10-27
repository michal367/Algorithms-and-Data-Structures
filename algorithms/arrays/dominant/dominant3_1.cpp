#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Dominant" << endl;
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

    int counters_size = b-a+1;
    int* counters = new int[counters_size];
    for(int i=0; i<counters_size; ++i)
        counters[i] = 0;


    for(int i=0; i<n; ++i)
        ++(counters[ar[i] - a]);

    bool is_mode_exist = false;
    int max_counter = 0;
    vector<int> mode_numbers;
    for(int i=0; i<counters_size; ++i)
    {
        if(counters[i] > max_counter)
        {
            if(max_counter > 0)
                is_mode_exist = true;
            max_counter = counters[i];
            mode_numbers.clear();
            mode_numbers.push_back(i + a);
        }
        else if(counters[i] == max_counter)
            mode_numbers.push_back(i + a);
        else
            is_mode_exist = true;
    }

    cout << endl;
    if(is_mode_exist)
    {
        if(mode_numbers.size() == 1)
            cout << "Dominant: " << mode_numbers.at(0) << endl
                 << "Amount: " << max_counter << endl;
        else
        {
            cout << "Dominants: ";
            for(vector<int>::iterator it = mode_numbers.begin(); it != mode_numbers.end(); ++it)
                cout << *it << " ";
            cout << endl << "Amount: " << max_counter << endl;
        }
    }
    else
        cout << "Dominant doesn't exist" << endl;


    delete[] ar;
    delete[] counters;

    cout << endl;
    system("pause");
    return 0;
}




