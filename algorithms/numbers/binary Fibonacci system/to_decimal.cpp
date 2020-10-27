#include <iostream>
#include <cstdlib>

using namespace std;

typedef unsigned long long ulong;

int main()
{
    cout << "Binary Fibonacci System" << endl;
    cout << "Conversion from binary Fibonacci system to decimal system" << endl
         << "n - number from binary Fibonacci system" << endl << endl;

    ulong n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);


    ulong m = n;
    int result = 0;
    int x = 1, y = 0;
    while(m != 0)
    {
        int l = m%10;
        if(l == 1)
            result += x;

        int temp = x;
        x += y;
        y = temp;

        m /= 10;
    }


    cout << result << endl;


    cout << endl;
    system("pause");
    return 0;
}


