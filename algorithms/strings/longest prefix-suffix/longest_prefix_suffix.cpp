#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Longest prefix-suffix" << endl
         << "str - text" << endl << endl;


    string str;
    cout << "str: ";
    getline(cin, str);
    cout << endl;

    bool is_exist = false;
    for(int i = str.size()-1; i > 0; --i)
    {
        if(str.substr(0, i) == str.substr(str.size()-i))
        {
            cout << "Longest prefix-suffix: " << i << " - " << str.substr(0, i);
            is_exist = true;
            break;
        }
    }

    if(!is_exist)
        cout << "None" << endl;



    cout << endl;
    system("pause");
    return 0;
}



