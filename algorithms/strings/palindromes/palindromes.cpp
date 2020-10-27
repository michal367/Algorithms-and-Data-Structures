#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
    cout << "Palindromes - find all palindromes in text with length>1" << endl
         << "str - text" << endl << endl;


    string str;
    cout << "str: ";
    cin >> str;
    cout << endl << endl;

    cout << str << endl;

    for(int i=0; i<str.size()-1; ++i)
    {
        for(int j=1; i+j<str.size(); ++j)
        {
            int k = i, l = i+j;
            while(k <= l && str[k] == str[l])
            {
                ++k;
                --l;
            }
            if(k > l)
            {
                for(int a=0; a<i; ++a)
                    cout << ' ';
                cout << str.substr(i, j+1) << endl;
            }
        }
    }



    cout << endl;
    system("pause");
    return 0;
}








