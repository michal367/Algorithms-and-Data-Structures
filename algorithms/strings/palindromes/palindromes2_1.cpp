#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
    cout << "Palindromes - Manacher's algorithm - find all palindromes in text with length>1" << endl
         << "str - text" << endl << endl;


    string str;
    cout << "str: ";
    cin >> str;
    cout << endl << endl;

    int** r = new int*[2]; // [0] - even , [1] - uneven
    for(int i = 0; i<2; ++i)
    {
        r[i] = new int[str.size()];
        r[i][0] = 0;
    }


    cout << str << endl;

    for(int t=0; t<2; ++t)
    {
        int rp = 0;
        for(int i=1; i<str.size();)
        {
            while(str[i - rp - 1] == str[i + rp + t])
                ++rp;
            r[t][i] = rp;

            int k=1;
            for(; r[t][i-k] != rp-k && k < rp; ++k)
                r[t][i+k] = min(r[t][i-k], rp-k);

            rp = max(rp-k, 0);
            i += k;
        }
    }


    for(int i=0; i<str.size(); ++i)
    {
        for(int t=0; t < 2; ++t)
        {
            for(int rp = r[t][i]; rp > 0; --rp)
            {
                for(int k=0;k < i-rp; ++k)
                    cout << ' ';
                cout << str.substr(i-rp, 2*rp + t) << endl;
            }
        }
    }


    cout << endl << "Radius arrays:" << endl;
    cout << "Even: ";
    for(int j=0; j<str.size(); ++j)
        cout << r[0][j] << ' ';
    cout << endl;
    cout << "Odd:  ";
    for(int j=0; j<str.size(); ++j)
        cout << r[1][j] << ' ';



    for(int i=0; i<2; ++i)
        delete[] r[i];
    delete[] r;

    cout << endl;
    system("pause");
    return 0;
}
