#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

long long x0;

long long random()
{
    x0 = (493*x0 + 385) % 984;
    return x0;
}

int main()
{
    cout << "Cipher - pseudo-random transposition" << endl
         << "seed - seed for LCG (key)" << endl
         << "str - text to encrypt" << endl << endl;

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
    int* rand_values = new int[str.size()];

    for(int i=0; i<str.size(); ++i)
    {
        rand_values[i] = random()%str.size();
        swap(str[i], str[rand_values[i]]);
    }

    cout << "Encrypted text: " << str << endl;


    for(int i=str.size()-1; i>=0; --i)
    {
        swap(str[i], str[rand_values[i]]);
    }

    cout << "Decrypted text: " << str << endl;

    cout << endl;
    system("pause");
    return 0;
}






