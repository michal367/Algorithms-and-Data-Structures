#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Hashtable - open addressing" << endl
         << "n - amount of texts" << endl
         << "str[i] - texts" << endl
         << "x - searched text" << endl << endl;

    size_t n;
    string str, x;
    cout << "n: ";
    cin >> n;
    cin.ignore();

    string* hash_table = new string[n];

    for(int i=0; i<n; ++i)
    {
        cout << "str[" << i << "]: ";
        getline(cin, str);


        int hash_value = 0;
        for(int i=0; i<str.size(); ++i)
            hash_value += int(str[i]);
        hash_value %= n;

        if(!hash_table[hash_value].empty())
        {
            int j = (hash_value+1) % n;
            while(!hash_table[j].empty() && j != hash_value)
                j = (j+1) % n;
            if(j == hash_value)
                cout << "Hashtable is full" << endl;
            else
                hash_table[j] = str;
        }
        else
            hash_table[hash_value] = str;
    }

    cout << endl;
    for(int i=0; i<n; ++i)
        cout << "hash_table[" << i << "]: " << hash_table[i] << endl;
    cout << endl;


    cout << "x: ";
    cin >> x;
    cout << endl;

    int hash_value = 0;
    for(int i=0; i<x.size(); ++i)
        hash_value += int(x[i]);
    hash_value %= n;

    if(hash_table[hash_value] == x)
        cout << "Found at position " << hash_value << endl;
    else
    {
        int j = (hash_value+1) % n;
        while(hash_table[j] != x && j != hash_value)
            j = (j+1) % n;
        if(j == hash_value)
            cout << "Not found" << endl;
        else
            cout << "Found at position " << j << endl;
    }

    delete[] hash_table;

    cout << endl;
    system("pause");
    return 0;
}




