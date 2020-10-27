#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Morris-Pratt algorithm for pattern searching" << endl
         << "str - text" << endl
         << "str2 - searched text" << endl << endl;

    string str, str2;
    cout << "str: ";
    getline(cin, str);
    cout << "str2: ";
    getline(cin, str2);


    int* mpnext = new int[str2.size() + 1];
    mpnext[0] = -1;
    mpnext[1] = 0;

    int ps = 0;
    for(int i=2; i < str2.size() + 1; ++i)
    {
        while(ps > -1 && str2[ps] != str2[i-1])
            ps = mpnext[ps];
        mpnext[i] = ++ps;
    }

    cout << endl << "MPNext array:" << endl;
    for(int i=0; i < str2.size() + 1; ++i)
        cout << i << ": " << mpnext[i] << endl;
    cout << endl;


    cout << "Found positions:" << endl;
    for(int i=0; i < str.size(); ++i)
    {
        bool is_found = true;
        for(int j=0; j < str2.size(); ++j)
        {
            if(str[i+j] != str2[j])
            {
                if(j > 0)
                {
                    int ps = mpnext[j];
                    while(ps > -1 && str2[ps] != str[i+j])
                        ps = mpnext[ps];
                    i += (j - ps);
                    j = ps;
                }
                else
                {
                    is_found = false;
                    break;
                }
            }
        }

        if(is_found)
            cout << i << ' ';
    }
    delete[] mpnext;



    cout << endl;
    system("pause");
    return 0;
}





