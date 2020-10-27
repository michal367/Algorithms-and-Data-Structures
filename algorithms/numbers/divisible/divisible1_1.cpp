#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "In the range <a,b> find all numbers divisible by one of the numbers in the given range <c;d>" << endl;
    int a,b, c,d;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    do{
        cin >> b;
    }while(b < a);
    cout << endl;
    cout << "c: ";
    cin >> c;
    cout << "d: ";
    do{
        cin >> d;
    }while(d < c);

    cout << endl << "Result:" << endl;
    for(int i=a; i <= b; ++i)
    {
        for(int j=c; j <= d; ++j)
            if(i%j == 0)
            {
                cout << i << " is divisible by " << j << endl;
                break;
            }
    }

    cout << endl;
    system("pause");
    return 0;
}
