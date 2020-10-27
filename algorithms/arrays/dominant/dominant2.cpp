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

    bool is_mode_exist = false;
    int mode_counter = 0;
    vector<int> mode_numbers;
    for(int i=0; i< n - mode_counter; ++i)
    {
        bool is_diff = true;
        for(vector<int>::iterator it = mode_numbers.begin(); it != mode_numbers.end(); ++it)
            if(*it == ar[i])
            {
                is_diff = false;
                break;
            }
        if(is_diff)
        {
            int counter = 1;
            for(int j=i+1; j<n; ++j)
                if(ar[j] == ar[i])
                    ++counter;

            if(counter > mode_counter)
            {
                if(mode_counter > 0)
                    is_mode_exist = true;
                mode_counter = counter;
                mode_numbers.clear();
                mode_numbers.push_back(ar[i]);
            }
            else if(counter == mode_counter)
            {
                mode_numbers.push_back(ar[i]);
            }
            else
                is_mode_exist = true;
        }
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



