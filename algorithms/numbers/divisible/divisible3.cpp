#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "In the range <a,b> find all numbers indivisible by any of the numbers from the given set P" << endl;
    int a,b, c;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    do{
        cin >> b;
    }while(b < a);
    cout << endl;

    vector<int> factors;
    cout << "P set divisors (0 - end): " << endl;
    do{
        cin >> c;
        if(c != 0)
            factors.push_back(c);
    }while(c != 0);


    cout << endl << "Result:" << endl;
    for(int i=a; i <= b; ++i)
    {
        bool is_indivisible = 1;
        for(vector<int>::iterator it = factors.begin(); it != factors.end(); ++it)
        {
            if(i%(*it) == 0)
            {
                is_indivisible = 0;
                break;
            }
        }
        if(is_indivisible)
            cout << i << " is not divisible by any of numbers of P" << endl;
    }



    cout << endl;
    system("pause");
    return 0;
}
