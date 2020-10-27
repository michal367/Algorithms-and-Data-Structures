#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
    cout << "Square words - find all square words in text" << endl
         << "square word is a word in the form ww, where w is subword" << endl
         << "str - text" << endl << endl;


    string str;
    cout << "str: ";
    cin >> str;
    cout << endl << endl;

    cout << str << endl;
    for(int i=0; i<str.size()-1; ++i)
        for(int n=2; i+n <= str.size(); n +=2)
        {
            int j = i+n/2;
            if(str.substr(i, j-i) == str.substr(j, j-i))
            {
                for(int a=0; a<i; ++a)
                    cout << ' ';
                cout << str.substr(i,n) << endl;
            }
        }


    cout << endl;
    system("pause");
    return 0;
}






