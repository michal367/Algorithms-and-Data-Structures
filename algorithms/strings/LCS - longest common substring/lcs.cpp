#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

int main()
{
    cout << "LCS - longest common substring" << endl
         << "str - first text" << endl
         << "str2 - second text" << endl << endl;


    string str, str2;
    cout << "str: ";
    getline(cin, str);
    cout << "str2: ";
    getline(cin, str2);
    cout << endl;


    int max_counter = 0, max_pos = 0;
    for(int i=0; i<str.size(); ++i)
    {
        for(int j=0; j<str2.size(); ++j)
        {
            int cur_counter = 0;
            for(; j + cur_counter < str2.size() && str[i + cur_counter] == str2[j + cur_counter] ; ++cur_counter);
            if(cur_counter > max_counter)
            {
                max_counter = cur_counter;
                max_pos = j;
            }
        }
    }


    cout << "Longest common substring: " << str2.substr(max_pos, max_counter) << endl
         << "Length: " << max_counter << endl;


    cout << endl;
    system("pause");
    return 0;
}

