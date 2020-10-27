#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;


int main()
{
    cout << "Cipher - neighbour transposition" << endl
         << "str - text to encrypt" << endl << endl;

    string str;
    cout << "str: ";
    getline(cin, str);
    cout << endl;

    for(int i=0; i<str.size()-1; i+=2)
        swap(str[i], str[i+1]);

    cout << "Encrypted text: " << str << endl;

    for(int i=0; i<str.size()-1; i+=2)
        swap(str[i], str[i+1]);

    cout << "Decrypted text: " << str << endl;

    cout << endl;
    system("pause");
    return 0;
}





