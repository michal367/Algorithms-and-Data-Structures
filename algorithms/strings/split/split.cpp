#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

int main()
{
    cout << "Splitting into words" << endl
         << "str - text" << endl << endl;


    string str;
    cout << "str: ";
    getline(cin, str);
    cout << endl;


    string str2;
    str += " ";
    for(int i=0; i<str.size(); ++i)
    {
        if(isalnum(str[i]))
            str2 += str[i];
        else if(!str2.empty())
        {
            cout << '[' << str2 << "] ";
            str2.clear();
        }
    }


    cout << endl;
    system("pause");
    return 0;
}





