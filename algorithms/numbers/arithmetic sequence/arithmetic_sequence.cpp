#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Generating n consecutive numbers of arithmetic sequence" << endl;
    int n;
    double a, r;
    cout << "n: ";
    do{
        cin >> n;
    }while(n <= 0);
    cout << "a1: ";
    cin >> a;
    cout << "r: ";
    cin >> r;

    cout << endl << "Result:" << endl;
    for(int i=1; i <= n; ++i)
        cout << i << ": " << (a + (i-1)*r) << endl;


    cout << endl;
    system("pause");
    return 0;
}
