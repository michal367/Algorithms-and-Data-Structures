#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Calculating a x b modulo n" << endl << endl;

    int a,b,n;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "n: ";
    cin >> n;
    cout << endl;

    cout << a << "*" << b << " mod " << n << " = " << a*b << " mod " << n << endl;

    int mod1 = (a*b)%n;
    int mod2 = ((a%n)*(b%n)) % n;

    cout << "way 1: " << mod1 << endl
         << "way 2: " << mod2 << endl;9


    cout << endl;
    system("pause");
    return 0;
}
