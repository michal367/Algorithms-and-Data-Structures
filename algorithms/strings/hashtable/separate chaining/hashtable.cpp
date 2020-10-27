#include <iostream>
#include <cstdlib>

#include <list>

using namespace std;


size_t hash_function(string str, size_t n)
{
    size_t hash_value = 0;
    for(int i=0; i<str.size(); ++i)
        hash_value += int(str[i]);
    hash_value %= n;
    return hash_value;
}

int main()
{
    cout << "Hashtable - separate chaining" << endl
         << "n - amount of texts" << endl
         << "str[i] - texts" << endl
         << "x - searched text" << endl << endl;

    size_t n;
    string str, x;
    cout << "n: ";
    cin >> n;
    cin.ignore();

    list<string>* hash_table = new list<string>[n];

    for(size_t i=0; i<n; ++i)
    {
        cout << "str[" << i << "]: ";
        cin >> str;
        size_t index = hash_function(str,n);
        hash_table[index].push_back(str);
    }


    cout << endl;
    for(size_t i=0; i < n; ++i)
    {
        cout << "hash_table[" << i << "]: ";
        for(auto it = hash_table[i].begin(); it != hash_table[i].end(); ++it)
            cout << *it << ' ';
        cout << endl;
    }


    cout << endl;
    cout << "x: ";
    cin >> x;
    cout << endl;

    size_t index = hash_function(x,n);
    bool is_found = false;
    for(auto it = hash_table[index].begin(); it != hash_table[index].end(); ++it)
    {
        if(*it == x)
        {
            cout << "Found" << endl;
            is_found = true;
        }
    }
    if(!is_found)
        cout << "Not found" << endl;



    delete[] hash_table;

    cout << endl;
    system("pause");
    return(0);
}
