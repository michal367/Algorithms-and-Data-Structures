#include <iostream>
#include <cstdlib>
#include <stack>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Insert Sort - stack implementation" << endl;
    cout << "n - size of an array with random values" << endl
         << "a - min value; b - max value" << endl << endl;

    size_t n;
    int a,b;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 0);
    cout << "a: ";
    cin >> a;
    cout << "b: " ;
    cin >> b;
    cout << endl;

    cout << "Generated array:" << endl;
    int* ar = new int[n];
    for(int i=0; i<n; ++i)
    {
        ar[i] = rand() % (b-a+1) + a;
        cout << i << ": " << ar[i] << endl;
    }


    //
    stack<int> left, right;
    left.push(a-1);
    right.push(b+1);

    for(int i=0; i<n; ++i)
    {
        while(ar[i] < left.top())
        {
            right.push(left.top());
            left.pop();
        }
        while(ar[i] > right.top())
        {
            left.push(right.top());
            right.pop();
        }
        left.push(ar[i]);
    }

    while(!left.empty())
    {
        right.push(left.top());
        left.pop();
    }

    cout << endl << "Sorted:" << endl;
    right.pop();
    while(right.size() != 1)
    {
        cout << right.top() << ' ';
        right.pop();
    }


    delete[] ar;


    cout << endl;
    system("pause");
    return 0;
}
