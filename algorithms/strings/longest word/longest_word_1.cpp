#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

int main()
{
    cout << "Longest word" << endl
         << "str - text" << endl << endl;


    string str;
    cout << "str: ";
    getline(cin, str);
    cout << endl;


    str += " ";
    int max_pos = 0, max_size = 0, cur_pos = 0, cur_size = 0;
    for(int i=0; i<str.size(); ++i)
    {
        if(isalnum(str[i]))
            ++cur_size;
        else
        {
            if(cur_size > 0)
            {
                if(cur_size > max_size)
                {
                    max_size = cur_size;
                    max_pos = cur_pos;
                }
                cur_size = 0;
            }
            cur_pos = i+1;
        }
    }

    cout << "Longest word: \"" << str.substr(max_pos, max_size) << "\"" << endl
         << "Length: " << max_size << endl;


    cout << endl;
    system("pause");
    return 0;
}







