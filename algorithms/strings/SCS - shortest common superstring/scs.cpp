#include <iostream>
#include <cstdlib>

using namespace std;


int main()
{
    cout << "SCS - shortest common superstring - greedy algorithm" << endl
         << "result can be not optimal" << endl
         << "k - amount of texts (k > 1)" << endl
         << "str(i) - text" << endl << endl;


    int k;
    cout << "k: ";
    do{
        cin >> k;
    }while(k <= 1);
    cin.ignore();

    string* strs = new string[k];
    for(int i=0; i<k; ++i)
    {
        cout << "str(" << i << "): ";
        getline(cin, strs[i]);
    }
    cout << endl;

    string* strs2 = new string[k];
    copy(strs, strs+k, strs2);


    // ==================

    string result = "";
    int max_common_str_size = 0;
    int max_i, max_j;

    for(int a=k; a > 1; --a)
    {
        max_i = -1;
        max_common_str_size = 0;

        for(int i=0; i < a; ++i)
            for(int j = 0; j < a; ++j)
                if(i != j)
                {
                    for(int m = min(strs[i].size(), strs[j].size()); m > 0; --m)
                        if(strs[i].substr(strs[i].size() - m) == strs[j].substr(0,m))
                            if(m > max_common_str_size)
                            {
                                max_common_str_size = m;
                                max_i = i;
                                max_j = j;
                                break;
                            }
                }

        if(max_i == -1)
        {
            max_i = 0;
            max_j = 1;
        }
        strs[max_i] += strs[max_j].substr(max_common_str_size);
        strs[max_j] = strs[a-1];
        result = strs[max_i];
    }




    int max_index = 0;
    for(int i=0; i<k; ++i)
    {
        cout << "strs[" << i << "]: ";
        int index = result.find(strs2[i]);
        for(int j=0; j<index; ++j)
            cout << " ";
        cout << strs2[i] << endl;
        index += strs2[i].size();
        if(index > max_index)
            max_index = index;
    }
    result.erase(max_index);
    cout << "         " << result << endl << endl;


    cout << endl;
    cout << "Shortest common superstring: " << result << endl
         << "Length: " << result.size() << endl;


    delete[] strs;
    delete[] strs2;

    cout << endl;
    system("pause");
    return 0;
}




