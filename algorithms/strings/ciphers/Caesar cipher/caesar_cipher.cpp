#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;


int main()
{
    cout << "Caesar cipher" << endl
         << "str - uppercase text to encrypt" << endl << endl;

    string str;
    cout << "str: ";
    getline(cin, str);
    cout << endl;

    int shift = 3;
    for(int i=0; i<str.size(); ++i)
    {
        if(isalpha(str[i]) && isupper(str[i]))
            str[i] = (str[i] - 'A' + shift) % 26 + 'A';
    }

    cout << "Encrypted text: " << str << endl;

    for(int i=0; i<str.size(); ++i)
    {
        if(isalpha(str[i]) && isupper(str[i]))
            str[i] = (str[i] - 'A' + 26 - shift) % 26 + 'A';
    }

    cout << "Decrypted text: " << str << endl;

    cout << endl;
    system("pause");
    return 0;
}




