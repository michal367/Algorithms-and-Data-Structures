#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
    cout << "Square word - check if word is square word" << endl
         << "square word is a word in the form ww, where w is subword" << endl
         << "str - text" << endl << endl;


    string str;
    cout << "str: ";
    cin >> str;
    cout << endl;


    bool is_square_word = false;
    if(str.size() % 2 == 0)
    {
        int i = 0, j = str.size()/2;
        while(j < str.size() && str[i] == str[j])
        {
            ++i;
            ++j;
        }
        if(j == str.size())
            is_square_word = true;
    }


    cout << endl;
    if(is_square_word)
        cout << "Word " << str << " is square word" << endl
             << "Identical substring: " << str.substr(0, str.size()/2) << endl;
    else
        cout << "Word " << str << " is not square word" << endl;


    cout << endl;
    system("pause");
    return 0;
}





