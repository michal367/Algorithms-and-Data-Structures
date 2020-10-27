#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

int main()
{
    cout << "LCS - longest common substring - dynamic programming" << endl
         << "str - first text" << endl
         << "str2 - second text" << endl << endl;


    string str, str2;
    cout << "str: ";
    getline(cin, str);
    cout << "str2: ";
    getline(cin, str2);
    cout << endl;


    int n = str.size()+1, m = str2.size()+1;

    int** lengths = new int*[n];
    for(int i=0; i<n; ++i)
    {
        lengths[i] = new int[m];
        for(int j=0; j<m; ++j)
            lengths[i][j] = 0;
    }


    int max_counter = 0, max_pos = 0;
    for(int i=0; i<str.size(); ++i)
    {
        for(int j=0; j<str2.size(); ++j)
        {
            if(str[i] != str2[j])
                lengths[i+1][j+1] = 0;
            else
            {
                lengths[i+1][j+1] = lengths[i][j] + 1;
                if(lengths[i+1][j+1] > max_counter)
                {
                    max_counter = lengths[i+1][j+1];
                    max_pos = i+1;
                }
            }
        }
    }


    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<m; ++j)
            cout<< lengths[i][j] << ' ';
        cout << endl;
    }


    cout << "Longest common substring: " << str.substr(max_pos-max_counter, max_counter) << endl
         << "Length: " << max_counter << endl;


    cout << endl;
    system("pause");
    return 0;
}


