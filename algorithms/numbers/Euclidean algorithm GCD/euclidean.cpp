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

    while(a != b)
    {
        if(a > b)
            a -= b;
        else
            b -= a;
    }

    cout << endl << "GCD: " << a << endl;

    cout << endl;
    system("pause");
    return 0;
}
