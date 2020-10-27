#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "In the range <a,b> find all numbers divisible by each of the numbers from the given set P containing relatively prime numbers" << endl;
    int a,b, c;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    do{
        cin >> b;
    }while(b < a);
    cout << endl;

    cout << "P set divisors (0 - end): " << endl;
    int product = 1;
    do{
        cin >> c;
        if(c != 0)
            product *= c;
    }while(c != 0);

    int temp = product;
    while(product < a)
        product += temp;
    while(product-temp > a)
        product -= temp;

    for(; product <= b; product += temp)
        cout << product << " is divisible by all numbers of P" << endl;


    cout << endl;
    system("pause");
    return 0;
}
