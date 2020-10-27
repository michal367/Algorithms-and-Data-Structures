#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
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


    vector<pair<int, int> > numbers;
    for(int i=0; i<n; ++i)
    {
        bool is_diff = true;
        for(vector<pair<int, int> >::iterator it = numbers.begin(); it != numbers.end(); ++it)
            if(it->first == ar[i])
            {
                is_diff = false;
                ++(it->second);
                break;
            }
        if(is_diff)
            numbers.push_back(pair<int,int>(ar[i], 1));
    }

    bool is_mode_exist = false;
    int max_counter = 0;
    vector<int> mode_numbers;
    for(vector<pair<int, int> >::iterator it = numbers.begin(); it != numbers.end(); ++it)
    {
        if(it->second > max_counter)
        {
            if(max_counter > 0)
                is_mode_exist = true;
            max_counter = it->second;
            mode_numbers.clear();
            mode_numbers.push_back(it->first);
        }
        else if(it->second == max_counter)
            mode_numbers.push_back(it->first);
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

    cout << endl;
    system("pause");
    return 0;
}



