#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
    cout << "Square words - Morris-Pratt algorithm - find all square words in text" << endl
         << "square word is a word in the form ww, where w is subword" << endl
         << "str - text" << endl << endl;


    string str;
    cout << "str: ";
    cin >> str;
    cout << endl << endl;

    cout << str << endl;

    int n = str.size()+1;
    int* pi_array = new int[n];
    pi_array[0] = -1;

    for(int i=0; i<str.size() - 1; ++i)
    {
        int ps = -1;
        for(int j=0; i+j<str.size(); ++j)
        {
            while(ps > -1 && str[i+ps] != str[i+j])
                ps = pi_array[ps];
            pi_array[j+1] = ++ps;

            if((j+1)%2 == 0)
            {
                if(2*ps == j+1)
                {
                    for(int a=0; a<i; ++a)
                        cout << ' ';
                    cout << str.substr(i,j+1) << endl;
                }
                else if(3*ps >= 2*j+2)
                {
                    int index = (2*ps-j-1) / 2;
                    if(str.substr(i,index) == str.substr(i+index,index))
                    {
                        for(int a=0; a<i; ++a)
                            cout << ' ';
                        cout << str.substr(i,j+1) << endl;
                    }
                }
            }
        }
    }
    delete[] pi_array;



    cout << endl;
    system("pause");
    return 0;
}







