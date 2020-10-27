#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
    cout << "Is natural number prime" << endl;
    cout << "Checking if a natural number n is prime" << endl << endl;

    unsigned int n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);
    cout << endl;

    if(n == 0 || n == 1)
        cout << "Number " << n << " is NOT prime" << endl;
    else
    {
        int square_root = sqrt(n);
        bool is_prime = true;
        for(int i=2; i <= square_root; ++i)
        {
            if(n%i == 0)
            {
                is_prime = false;
                break;
            }
        }
        if(is_prime)
            cout << "Number " << n << " is prime" << endl;
        else
            cout << "Number " << n << " is NOT prime" << endl;
    }


    cout << endl;
    system("pause");
    return 0;
}
