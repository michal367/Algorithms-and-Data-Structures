#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;


string lcs(string str1, string str2)
{
    string result = "";
    if(str1[0] != str2[0])
    {
        string result2 = "", result3 = "";
        if(str1.size() > 1)
            result2 += lcs(str1.substr(1), str2);
        if(str2.size() > 1)
            result3 += lcs(str1, str2.substr(1));

        if(result2.size() >= result3.size())
            result += result2;
        else
            result += result3;
    }
    else
    {
        result += str1[0];
        if(str1.size() > 1 && str2.size() > 1)
            result += lcs(str1.substr(1), str2.substr(1));
    }
    return result;
}


int main()
{
    cout << "LCS - longest common subsequence" << endl
         << "str - first text" << endl
         << "str2 - second text" << endl << endl;


    string str, str2;
    cout << "str: ";
    getline(cin, str);
    cout << "str2: ";
    getline(cin, str2);
    cout << endl;


    string lcs_str = lcs(str, str2);

    cout << "Longest common subsequence: " << lcs_str << endl
         << "Length: " << lcs_str.size() << endl;


    cout << endl;
    system("pause");
    return 0;
}


