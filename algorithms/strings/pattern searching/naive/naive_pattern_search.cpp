#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Naive pattern search" << endl
         << "str - text" << endl
         << "str2 - searched text" << endl << endl;

    string str, str2;
    cout << "str: ";
    getline(cin, str);
    cout << "str2: ";
    getline(cin, str2);



    cout << endl << str << endl;

    for(int i = 0; i < str.size(); ++i)
    {
        bool is_found  = true;
        for(int j = 0; j < str2.size(); ++j)
        {
            if(str[i+j] != str2[j])
            {
                is_found = false;
                break;
            }
        }
        if(is_found)
            cout << "^";
        else
            cout << " ";
    }


    cout << endl;
    system("pause");
    return 0;
}
