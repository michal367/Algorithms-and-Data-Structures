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

    int** r = new int*[2]; // [0] - even , [1] - odd
    for(int i = 0; i<2; ++i)
    {
        r[i] = new int[str.size()];
        r[i][0] = 0;
        for(int j=1; j<str.size(); ++j)
            r[i][j] = -1;
    }


    cout << str << endl;

    for(int i=1; i<str.size(); ++i)
    {
        for(int t=0; t<2; ++t)
        {
            if(r[t][i] == -1)
            {
                int k=0;
                while(i-k-1 >= 0 && str[i-k-1] == str[i+k+t])
                {
                    ++k;
                    for(int a=0; a<i-k; ++a) cout << ' ';
                    cout << str.substr(i-k, 2*k+t) << endl;
                }
                r[t][i] = k;
            }

            if(r[t][i] > 0)
            {
                for(int k = 1; k < r[t][i]; ++k)
                {
                    int r1 = r[t][i-k-1], r2;
                    if(k + r1 < r[t][i])
                    {
                        r[t][i+k] = r2 = r1;
                    }
                    else if(k + r1 == r[t][i])
                    {
                        r2=r1;
                        if(r2 >= str.size()-(i+k+1))
                            r2 = str.size() - (i+k+1) - 1;
                        else
                            while(str[i+k-r2-1] == str[i+k+r2+t])
                            {
                                ++r2;
                                for(int a=0; a<i+k-r2-1; ++a) cout << ' ';
                                cout << str.substr(i+k-r2-1, 2*r2+t) << endl;
                            }
                        r[t][i+k] = r2;
                    }
                    else
                    {
                        r[t][i+k] = r2 = r[t][i] - k;
                    }

                    if(r2 > 0)
                    {
                        for(int a=0; a<i+k+1-r2+t; ++a) cout << ' ';
                        cout << str.substr(i+k+1-r2+t, 2*r2) << endl;
                    }
                }
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









