#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Knuth-Morris-Pratt algorithm for pattern searching" << endl
         << "str - text" << endl
         << "str2 - searched text" << endl << endl;

    string str, str2;
    cout << "str: ";
    getline(cin, str);
    cout << "str2: ";
    getline(cin, str2);


    int* kmpnext = new int[str2.size() + 1];
    kmpnext[0] = -1;

    int ps = -1;
    for(int i=1; i < str2.size() + 1; ++i)
    {
        while(ps > -1 && str2[ps] != str2[i-1])
            ps = kmpnext[ps];
        ++ps;

        if(str2[ps] != str2[i])
            kmpnext[i] = ps;
        else
            kmpnext[i] = kmpnext[ps];
    }


    cout << endl << "KMPNext array:" << endl;
    for(int i=0; i < str2.size() + 1; ++i)
        cout << i << ": " << kmpnext[i] << endl;
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
                    int ps = kmpnext[j];
                    while(ps > -1 && str2[ps] != str[i+j])
                        ps = kmpnext[ps];
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
    delete[] kmpnext;



    cout << endl;
    system("pause");
    return 0;
}






