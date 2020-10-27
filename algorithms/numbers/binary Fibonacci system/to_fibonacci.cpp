#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

typedef unsigned long long ulong;

int main()
{
    cout << "Binary Fibonacci System" << endl;
    cout << "Conversion from decimal system to binary Fibonacci system" << endl
         << "n - number from decimal system" << endl << endl;

    ulong n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);

    if(n == 1){
        cout << 1 << endl;
        system("pause");
        return 0;
    }

    vector<int> fibonnaci_numbers;
    int x = 1, y = 0;
    while(x < n)
    {
        fibonnaci_numbers.push_back(x);
        int temp = x;
        x += y;
        y = temp;
    }

    ulong m = n;
    string result = "";
    vector<int>::reverse_iterator rit = fibonnaci_numbers.rbegin();
    while(rit != fibonnaci_numbers.rend())
    {
        if(*rit <= m)
        {
            result += "1";
            m -= *rit;
        }
        else
        {
            result += "0";
        }
        ++rit;
    }


    cout << result << endl;


    cout << endl;
    system("pause");
    return 0;
}



