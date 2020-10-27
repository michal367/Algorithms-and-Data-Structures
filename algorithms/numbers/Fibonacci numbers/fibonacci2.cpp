#include <iostream>
#include <cstdlib>

using namespace std;

int fibonnaci(int n)
{
    int x = 0, y = 1;
    for(int i=1; i<n; ++i)
    {
        int temp = x;
        x += y;
        y = temp;
    }
    return x;
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

