#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Even numbers in the range <a;b>" << endl;
    int a,b;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    do{
        cin >> b;
    }while(b < a);

    int c = a;
    if(c%2 != 0)
        ++c;

    cout << endl << "Numbers:" << endl;
    for(int i=1; c <= b; c += 2, ++i)
        cout << i << ": " << c << endl;

    cout << endl;
    system("pause");
    return 0;
}
