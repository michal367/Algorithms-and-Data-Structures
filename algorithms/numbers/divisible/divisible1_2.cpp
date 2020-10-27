#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "In the range <a,b> find all numbers divisible by one of the numbers in the given set P" << endl;
    int a,b, c;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    do{
        cin >> b;
    }while(b < a);
    cout << endl;

    vector<int> dzielniki;
    cout << "P set divisors (0 - end): " << endl;
    do{
        cin >> c;
        if(c != 0)
            dzielniki.push_back(c);
    }while(c != 0);

    vector<int> dzielniki2 = dzielniki;
    vector<int>::iterator it = dzielniki2.begin();
    for(; it != dzielniki2.end(); ++it)
    {
        int temp = *it;
        while(*it < a)
            *it += temp;
        while(*it-temp > a)
            *it -= temp;
        cout << *it << "  ";
    }


    cout << endl << "Result:" << endl;
    it = dzielniki2.begin();
    vector<int>::iterator it2 = dzielniki.begin();
    for(; it != dzielniki2.end(); ++it, ++it2)
    {
        while(*it <= b)
        {
            cout << *it << " is divisible by " << *it2 << endl;
            *it += *it2;
        }
    }



    cout << endl;
    system("pause");
    return 0;
}
