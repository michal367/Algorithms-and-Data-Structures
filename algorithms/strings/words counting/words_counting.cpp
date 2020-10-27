#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

int main()
{
    cout << "Words counting" << endl
         << "str - text" << endl << endl;


    string str;
    cout << "str: ";
    getline(cin, str);


    bool is_word_started = false;
    int word_counter = 0;
    for(int i=0; i<str.size(); ++i)
    {
        if(!is_word_started && isalnum(str[i]))
        {
            is_word_started = true;
            ++word_counter;
        }
        else if(is_word_started && !isalnum(str[i]))
            is_word_started = false;
    }

    cout << endl << "Amount of words: " << word_counter << endl;

    cout << endl;
    system("pause");
    return 0;
}




