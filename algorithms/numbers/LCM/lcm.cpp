#include <iostream>
#include <cstdlib>

using namespace std;

int GCD(int a, int b);

int main()
{
    cout << "LCM - Least Common Multiple" << endl;

    int a, b;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    int lcm = (a*b)/GCD(a,b);

    cout << "LCM(" << a << "," << b << ") = " << lcm << endl;

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
