#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
    cout << "LCS - longest common subsequence - dynamic programming" << endl
         << "str - first text" << endl
         << "str2 - second text" << endl << endl;


    string str, str2;
    cout << "str: ";
    getline(cin, str);
    cout << "str2: ";
    getline(cin, str2);
    cout << endl;


    int n = str.size()+1, m = str2.size()+1;

    int** lengths = new int*[n];
    for(int i=0; i<n; ++i)
    {
        lengths[i] = new int[m];
        for(int j=0; j<m; ++j)
            lengths[i][j] = 0;
    }



    for(int i=0; i<n-1; ++i)
        for(int j=0; j<m-1; ++j)
        {
            if(str[i] == str2[j])
                lengths[i+1][j+1] = lengths[i][j] + 1;
            else
                lengths[i+1][j+1] = max(lengths[i+1][j], lengths[i][j+1]);
        }
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<m-1; ++j)
            cout << lengths[i][j] << ' ';
        cout << lengths[i][m-1] << endl;
    }



    string result = "";
    int i = n-2, j = m-2;
    while(i >=0 && j >= 0)
    {
        if(str[i] == str2[j])
        {
            result = str[i] + result;
            --i;
            --j;
        }
        else if(lengths[i+1][j] >= lengths[i][j+1])
            --j;
        else
            --i;
    }


    cout << endl;
    cout << "Longest common subsequence: " << result << endl
         << "Length: " << result.size() << endl;


    cout << endl;
    system("pause");
    return 0;
}



