#include <iostream>
#include <cstdlib>

using namespace std;

int GCD(int a, int b);

int main()
{
    cout << "Coprime integers" << endl;
    cout << "In the <a,b> range of natural numbers find all coprime integers with given number p" << endl << endl;

    int a, b, p;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    cout << "p: ";
    cin >> p;
    cout << endl;

    for(int i = a; i <= b; ++i)
    {
        int gcd = GCD(i,p);
        cout << "GCD(" << i << "," << p << ") = " << gcd <<endl;

        if(gcd == 1)
            cout << "Number " << i << " is coprime with " << p << endl;
        else
            cout << "Number " << i << " is NOT coprime with " << p << endl;
    }

    cout << endl;
    system("pause");
    return 0;
}

int GCD(int a, int b)
{
    while(b != 0)
    {
        int temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}
