#include <iostream>
#include <cstdlib>

using namespace std;

int fibonnaci(int n)
{
    if(n == 1)
        return 0;
    else if(n == 2)
        return 1;
    else
        return (fibonnaci(n-1) + fibonnaci(n-2));
}


int main()
{
    cout << "Fibonacci numbers" << endl;
    cout << "n - n'th number" << endl << endl;

    int n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n <= 0);


    cout << fibonnaci(n) << endl;


    cout << endl;
    system("pause");
    return 0;
}
