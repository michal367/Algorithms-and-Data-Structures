#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Extended Euclidean algorithm (modular multiplicative inverse)" << endl << endl;

    int a,b;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    int u,v,w, x,y,z;

    if(a >= b)
    {
        u = 0; v = 1; w = a; // (1)
        x = 1; y = 0; z = b; // (2)
    }
    else
    {
        u = 1; v = 0; w = b; // (1)
        x = 0; y = 1; z = a; // (2)
    }

    while(z != 0)
    {
        int z2 = z;

        int q = w/z;
        x -= q*u;
        y -= q*v;
        z = w%z;

        w = z2;
        swap(u,x);
        swap(v,y);
    }

    cout << endl << "x: " << x << endl;
    cout << "y: " << y << endl;

    cout << endl << "GCD(" << a << "," << b << ") = " << w << endl;
    cout << x << " * " << a << " + " << y << " * " << b << " = " << w << endl;

    cout << endl;
    system("pause");
    return 0;
}
