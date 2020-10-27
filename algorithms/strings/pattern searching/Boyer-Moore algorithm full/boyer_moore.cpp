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
    cout << "Boyer-Moore algorithm for pattern searching" << endl
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


    int n = str2.size();
    int* pi_array = new int[n+1];
    pi_array[n] = n+1;
    int* bmnext = new int[n+1];
    for(int i=0; i<n+1; ++i)
        bmnext[i] = 0;

    int ps = n+1;
    for(int i=n-1; i >= 0; --i)
    {
        while(ps < n+1 && str2[ps-1] != str2[i])
        {
            if(bmnext[ps] == 0)
                bmnext[ps] = ps-i-1;
            ps = pi_array[ps];
        }

        --ps;
        pi_array[i] = ps;
    }

    int ps2 = pi_array[0];
    for(int i=0; i<n+1; ++i)
    {
        if(bmnext[i] == 0)
            bmnext[i] = ps2;
        if(i == ps2)
            ps2 = pi_array[ps2];
    }


    cout << "Pi array:" << endl;
    for(int i=0; i < n + 1; ++i)
        cout << i << ": " << pi_array[i] << endl;
    cout << "BMNext array:" << endl;
    for(int i=0; i < n + 1; ++i)
        cout << i << ": " << bmnext[i] << endl;
    cout << endl;



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
                        i += bmnext[0];
                    }
                    --j;
                }
                else
                {
                    i += max(j - last_char(last, str[i+j]), bmnext[j+1]);
                    break;
                }
            }
        }

    delete[] pi_array;
    delete[] bmnext;


    cout << endl;
    system("pause");
    return 0;
}








