#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;


int main()
{
    cout << "Number system conversion from decimal to other from 2 to 36" << endl
         << "p - system to convert to (from 2 to 36)" << endl
         << "n - number" << endl << endl;

    int p;
    unsigned long long n;
    cout << "p: ";
    do{
        cin >> p;
    }while(p < 2 || p > 36);

    cout << "n: ";
    cin >> n;
    cout << endl;


    stack<int> numbers;
    while(n != 0)
    {
        numbers.push(n % p);
        n /= p;
    }

    while(!numbers.empty())
    {
        int digit = numbers.top();
        numbers.pop();

        if(digit >= 10)
            cout << char('a' + digit-10);
        else
            cout << digit;
    }

    cout << endl;
    system("pause");
    return 0;
}
