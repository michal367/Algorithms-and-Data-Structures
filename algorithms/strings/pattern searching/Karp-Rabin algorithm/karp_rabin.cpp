#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


void make_hash_alphabet(vector<pair<char, int> >& hash_alphabet, string str)
{
    int code = 0;
    if(hash_alphabet.size() > 0)
        code = hash_alphabet.back().second + 1;

    for(int i = 0; i < str.size(); ++i)
    {
        bool is_found = false;
        for(int j=0; j<hash_alphabet.size(); ++j)
            if(hash_alphabet.at(j).first == str[i])
                is_found = true;
        if(!is_found)
        {
            hash_alphabet.push_back(pair<char, int>(str[i],code));
            ++code;
        }
    }
}

int get_code_of_hash_alphabet(vector<pair<char, int> >& hash_alphabet, char c)
{
    vector<pair<char, int> >::iterator it = hash_alphabet.begin();
    for(; it != hash_alphabet.end(); ++it)
        if(it->first == c)
            return it->second;
}

int main()
{
    cout << "Karp-Rabin algorithm for pattern searching" << endl
         << "str - text" << endl
         << "str2 - searched text" << endl << endl;

    string str, str2;
    cout << "str: ";
    getline(cin, str);
    cout << "str2: ";
    getline(cin, str2);



    vector<pair<char, int> > hash_alphabet;
    make_hash_alphabet(hash_alphabet, str);
    make_hash_alphabet(hash_alphabet, str2);

    const int hash_modulo = 179426549;
    const int hash_base = hash_alphabet.back().second + 1;

    cout << endl << "Hash alphabet:" << endl;
    for(int i=0; i<hash_alphabet.size(); ++i)
        cout << hash_alphabet.at(i).first << ": " << hash_alphabet.at(i).second << endl;



    int hash_number = 0;
    int hash_base_power = 1;
    for(int i = str2.size()-1; i >= 0 ; --i)
    {
        hash_number += (get_code_of_hash_alphabet(hash_alphabet, str2[i]) * hash_base_power) % hash_modulo;
        hash_base_power *= hash_base;
    }
    hash_number %= hash_modulo;
    cout << "pattern hash number: " << hash_number << endl;

    cout << endl << "Found positions:" << endl;
    if(str.size() >= str2.size())
    {
        int hash_number2 = 0;
        int hash_base_power = 1;
        for(int i = str2.size()-1; i >= 0 ; --i)
        {
            hash_number2 += (get_code_of_hash_alphabet(hash_alphabet, str[i]) * hash_base_power) % hash_modulo;
            hash_base_power *= hash_base;
        }
        hash_base_power /= hash_base;
        hash_number2 %= hash_modulo;
        if(hash_number == hash_number2 && str2 == str.substr(0, str2.size()))
            cout << 0 << ' ';

        for(int i=1; i<str.size() - str2.size() + 1; ++i)
        {
            hash_number2 -= (get_code_of_hash_alphabet(hash_alphabet, str[i-1]) * hash_base_power) % hash_modulo;
            hash_number2 *= hash_base;
            hash_number2 += (get_code_of_hash_alphabet(hash_alphabet, str[i + str2.size() - 1])) % hash_modulo;

            if(hash_number == hash_number2 && str2 == str.substr(i, str2.size()))
                cout << i << ' ';
        }
    }



    cout << endl;
    system("pause");
    return 0;
}






