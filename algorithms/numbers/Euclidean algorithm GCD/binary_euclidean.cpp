#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Euclidean algorithm - GCD" << endl
         << "For given two natural numbers a and b, find the greatest natural number c that divides a and b completely" << endl;

    int a,b, c;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    cout << endl;

    if(a == 0)
        cout << "GCD: " << b << endl;
    else if(b == 0)
        cout << "GCD: " << a << endl;
    else
    {
        int k = 0;
        while((a&1) == 0 && (b&1) == 0)
        {
            a = a >> 1;
            b = b >> 1;
            ++k;
        }
        while(b != 0)
        {
            if(a == 0)
            {
                a = b;
                break;
            }
            while((a&1) == 0)
                a = a >> 1;
            while((b&1) == 0)
                b = b >> 1;
            if(a >= b)
                a = (a-b) >> 1;
            else
            {
                int temp = (b-a) >> 1;
                b = a;
                a = temp;
            }
        }
        if(k > 0)
            a = a << k;
        cout << "GCD: " << a << endl;
    }


    cout << endl;
    system("pause");
    return 0;
}

