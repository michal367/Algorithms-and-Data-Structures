#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Naive pattern search with sentinel" << endl
         << "str - text" << endl
         << "str2 - searched text" << endl << endl;

    string str, str2;
    cout << "str: ";
    getline(cin, str);
    cout << "str2: ";
    getline(cin, str2);



    cout << endl << str << endl;

    str += str2;

    for(int i = 0;; ++i)
    {
        if(str2 == str.substr(i, str2.size()))
        {
            if(i != str.size() - str2.size())
                cout << "^";
            else
                break;
        }
        else
            cout << " ";
    }



    cout << endl;
    system("pause");
    return 0;
}


