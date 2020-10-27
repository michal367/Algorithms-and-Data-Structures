#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Longest prefix-suffix - Morris-Pratt algorithm" << endl
         << "str - text" << endl << endl;

    string str;
    cout << "str: ";
    getline(cin, str);


    int* mpnext = new int[str.size() + 1];
    mpnext[0] = -1;
    mpnext[1] = 0;

    int ps = 0;
    for(int i=2; i < str.size() + 1; ++i)
    {
        if(str[ps] == str[i-1])
            ++ps;
        else if(ps > 0)
        {
            ps = mpnext[ps];
            if(str[ps] == str[i-1])
                ++ps;
        }
        mpnext[i] = ps;
    }

    cout << "MPNext array:" << endl;
    for(int i=0; i < str.size() + 1; ++i)
    {
        cout << i << ": " << mpnext[i] << endl;
    }
    delete[] mpnext;

    cout << endl;
    if(ps == 0)
        cout << "None" << endl;
    else
        cout << "Longest prefix-suffix: " << ps << " - " << str.substr(0,ps) << endl;



    cout << endl;
    system("pause");
    return 0;
}




