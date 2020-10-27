#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;


int last_char(vector<pair<char, int> >& last, char c)
{
    for(int i=0; i<last.size(); ++i)
    {
        if(last.at(i).first == c)
            return last.at(i).second;
    }
    return -1;
}


int main()
{
    cout << "Simplified Boyer-Moore algorithm for pattern searching" << endl
         << "str - text" << endl
         << "str2 - searched text" << endl << endl;

    string str, str2;
    cout << "str: ";
    getline(cin, str);
    cout << "str2: ";
    getline(cin, str2);



    vector<pair<char, int> > last;

    for(int i = 0; i < str2.size(); ++i)
    {
        bool is_found = false;
        for(int j=0; j<last.size(); ++j)
        {
            if(last.at(j).first == str2[i])
            {
                is_found = true;
                last.at(j).second = i;
            }
        }
        if(!is_found)
            last.push_back(pair<char, int>(str2[i],i));
    }

    cout << endl << "Last occurrences:" << endl;
    for(int i=0; i<last.size(); ++i)
        cout << last.at(i).first << ": " << last.at(i).second << endl;


    cout << endl << "Found positions:" << endl;
    if(str2.size() <= str.size())
        for(int i = 0; i < str.size() - str2.size() + 1;)
        {
            for(int j = str2.size() - 1; j >= 0;)
            {
                if(str[i+j] == str2[j])
                {
                    if(j == 0)
                    {
                        cout << i << ' ';
                        ++i;
                    }
                    --j;
                }
                else
                {
                    i += max(j - last_char(last, str[i+j]), 1);
                    break;
                }
            }
        }



    cout << endl;
    system("pause");
    return 0;
}







