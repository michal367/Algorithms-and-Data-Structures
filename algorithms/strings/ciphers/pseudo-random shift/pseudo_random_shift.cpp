#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

long long x0;

long long random()
{
    x0 = (1978141*x0 + 1309) % 3956280000;
    return x0;
}

int main()
{
    cout << "Cipher - pseudo-random shift" << endl
         << "seed - seed for LCG (key)" << endl
         << "str - uppercase text to encrypt" << endl << endl;

    long long seed;
    string str;
    cout << "seed: ";
    do{
        cin >> seed;
    }while(seed < 0);
    cin.ignore();
    cout << "str: ";
    getline(cin, str);
    cout << endl;


    x0 = seed;
    for(int i=0; i<str.size(); ++i)
    {
        if(isalpha(str[i]) && isupper(str[i]))
            str[i] = (str[i] - 'A' + (random()%26)) % 26 + 'A';
    }

    cout << "Encrypted text: " << str << endl;


    x0 = seed;
    for(int i=0; i<str.size(); ++i)
    {
        if(isalpha(str[i]) && isupper(str[i]))
            str[i] = (str[i] - 'A' + 26 - (random()%26)) % 26 + 'A';
    }

    cout << "Decrypted text: " << str << endl;

    cout << endl;
    system("pause");
    return 0;
}





