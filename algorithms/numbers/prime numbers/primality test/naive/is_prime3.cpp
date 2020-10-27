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
        bool is_prime = true;
        if(n > 2 && n%2 == 0)
            is_prime = false;
        else if(n > 3 && n%3 == 0)
            is_prime = false;
        else
        {
            int square_root = sqrt(n);
            for(int i=5; i <= square_root; i += 4)
            {
                if(n%i == 0)
                {
                    is_prime = false;
                    break;
                }
                i += 2;
                if(n%i == 0)
                {
                    is_prime = false;
                    break;
                }
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


