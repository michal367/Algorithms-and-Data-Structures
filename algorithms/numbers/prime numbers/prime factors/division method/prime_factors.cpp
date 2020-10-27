#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
    cout << "Prime factors - division method" << endl;
    cout << "Decomposition of the number n into prime factors" << endl << endl;

    unsigned int n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 2);


    cout << endl << "Prime factors:" << endl;
    unsigned int m = n;
    for(unsigned int i=2; i <= m; ++i)
    {
        while(m % i == 0)
        {
            m /= i;
            cout << i << endl;
        }
    }


    cout << endl;
    system("pause");
    return 0;
}
