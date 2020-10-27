#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

int main()
{
    cout << "Longest word" << endl
         << "str - text" << endl << endl;


    string str;
    cout << "str: ";
    getline(cin, str);
    cout << endl;


    str += " ";
    string current_word, max_word;
    for(int i=0; i<str.size(); ++i)
    {
        if(isalnum(str[i]))
            current_word += str[i];
        else if(!current_word.empty())
        {
            if(current_word.size() > max_word.size())
                max_word = current_word;
            current_word.clear();
        }
    }

    cout << "Longest word: \"" << max_word << "\"" << endl
         << "Length: " << max_word.size() << endl;


    cout << endl;
    system("pause");
    return 0;
}






