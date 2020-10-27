#include <iostream>
#include <cstdlib>
#include <map>

#include "Coding.h"

using namespace std;

int main()
{
    Coding hc;

    string data[] = {"ABCDEF", "AAAABBBBDDD"};
    size_t data_s = 2;
    for(int i=0; i<data_s; ++i)
    {
        cout << "text: " << data[i] << endl;

        Coding cd;
        string encoded = cd.encode(data[i]);
        cout << "encoded: " << encoded << endl;

        cout << endl << "prefix-free coding:" << endl;
        cd.PRINT();
        cout << endl;

        string decoded = cd.decode();
        cout << "decoded: " << decoded << endl;

        std::cout << "==========================" << std::endl;
    }

    std::cout << "==========================" << std::endl;
    std::cout << "==========================" << std::endl;
    cout << "Coding with code" << endl;
    map<char, string> letters;
    letters['A'] = "0";
    letters['B'] = "100";
    letters['C'] = "101";
    letters['D'] = "110";
    letters['E'] = "111";
    string str = "ABCDEACABBBDDCEDAB";

    cout << "text: " << str << endl;
    cout << endl << "code:" << endl;
    for(auto it = letters.begin(); it != letters.end(); it++)
        cout << it->first << ": " << it->second << endl;

    Coding cd2;
    cd2.encode(letters, str);

    cout << endl << "prefix-free coding:" << endl;
    cd2.PRINT();

    cout << endl << "decoded: " << cd2.decode() << endl;

    cout << endl;
    return 0;
}
