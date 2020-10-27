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


    while(m%2 == 0)
    {
        m /= 2;
        cout << 2 << endl;
    }
    while(m%3 == 0)
    {
        m /= 3;
        cout << 3 << endl;
    }

    for(unsigned int i=1, j = 6*i-1; j+2 <= m; ++i)
    {
        j = 6*i-1;
        while(m%j == 0)
        {
            m /= j;
            cout << j << endl;
        }
        j += 2;
        while(m%j == 0)
        {
            m /= j;
            cout << j << endl;
        }
    }



    cout << endl;
    system("pause");
    return 0;
}
