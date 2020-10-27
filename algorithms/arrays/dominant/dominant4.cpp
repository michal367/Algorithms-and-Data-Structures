#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
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
    for(int i=0; i<n; ++i)
        ar[i] = rand() % (b-a+1) + a;

    sort(ar, ar+n);

    cout << "Generated sorted array:" << endl;
    for(int i=0; i<n; ++i)
        cout << i << ": " << ar[i] << endl;

    bool is_mode_exist = false;
    int counter = 1, mode_counter = 0;
    vector<int> mode_numbers;
    for(int i=1; i<n; ++i)
    {
        if(ar[i-1] != ar[i])
        {
            if(counter > mode_counter)
            {
                if(mode_counter > 0)
                    is_mode_exist = true;
                mode_counter = counter;
                mode_numbers.clear();
                mode_numbers.push_back(ar[i-1]);
            }
            else if(counter == mode_counter)
                mode_numbers.push_back(ar[i-1]);
            else
                is_mode_exist = true;

            counter = 0;
        }
        ++counter;
    }

    cout << endl;
    if(is_mode_exist)
    {
        if(mode_numbers.size() == 1)
            cout << "Dominant: " << mode_numbers.at(0) << endl
                 << "Amount: " << mode_counter << endl;
        else
        {
            cout << "Dominants: ";
            for(vector<int>::iterator it = mode_numbers.begin(); it != mode_numbers.end(); ++it)
                cout << *it << " ";
            cout << endl << "Amount: " << mode_counter << endl;
        }
    }
    else
        cout << "Dominant doesn't exist" << endl;


    delete[] ar;

    cout << endl;
    system("pause");
    return 0;
}




