#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;


int main()
{
    cout << "Cipher - array transposition" << endl
         << "str - text to encrypt" << endl << endl;

    string str;
    cout << "str: ";
    getline(cin, str);
    cout << endl;


    int n=1, n2=1, diff=3;
    while(n2 <= str.size())
    {
        ++n;
        n2 += diff;
        diff += 2;
    }
    //--n;


    while(str.size() < n*n)
        str += '.';

    cout << "new str: " << str << endl;
    cout << "n: " << n << endl << endl;

    string str2;
    int a=0;
    for(int i=0; i<n; ++i)
        for(int j=0; j<str.size(); j+=n)
            str2 += str[i+j];

    cout << "Encrypted text: " << str2 << endl;


    string str3;
    a=0;
    for(int i=0; i<n; ++i)
        for(int j=0; j<str2.size(); j+=n)
            str3 += str2[i+j];

    cout << "Decrypted text: " << str3 << endl;

    cout << endl;
    system("pause");
    return 0;
}






