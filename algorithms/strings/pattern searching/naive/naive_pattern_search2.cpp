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

    for(int i = 0; i < str.size() - str2.size() + 1; ++i)
    {
        if(str2 == str.substr(i, str2.size()))
            cout << "^";
        else
            cout << " ";
    }



    cout << endl;
    system("pause");
    return 0;
}

