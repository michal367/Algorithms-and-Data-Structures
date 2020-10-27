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


    int u = 1, v = 0, w = a; // (1)
    int x = 0, y = 1, z = b; // (2)

    while(w != 0)
    {
        if(w < z)
        {
            swap(u,x);
            swap(v,y);
            swap(w,z);
        }
        int q = w/z;

        // (1) - q*(2)
        u -= q*x;
        v -= q*y;
        w = w%z;

        //cout << "q: "<<q << endl;
        //cout << "w: "<<w << "   " << "z: "<<z << endl;
    }

    cout << endl << "x: " << x << endl << "y: " << y << endl;

    cout << endl << "GCD(" << a << "," << b << ") = " << z << endl;
    cout << x << " * " << a << " + " << y << " * " << b << " = " << z << endl;


    cout << endl;
    system("pause");
    return 0;
}



