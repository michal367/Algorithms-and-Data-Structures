#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

long long random_Mersenne_Twister_19937(unsigned int* mt_array)
{
    static int mt_index = 0;
    unsigned int ma[] = {0, 0x9908b0df};

    long long y = (mt_array[mt_index] & 0x80000000) | (mt_array[(mt_index + 1) % 624] & 0x7fffffff);
    mt_array[mt_index] = mt_array[(mt_index + 397) % 624] ^ (y >> 1) ^ ma[y & 1];
    y = mt_array[mt_index];
    y = y ^ (y >> 11);
    y = y ^ ((y << 7) & 0x9d2c5680);
    y = y ^ ((y << 15) & 0xefc60000);
    y = y ^ (y >> 18);
    mt_index = (mt_index + 1) % 624;
    return y;
}


int main()
{
    srand(time(NULL));

    cout << "Mersenne Twister pseudo-random number generator" << endl;
    cout << "x_max - max value" << endl
         << "k - amount of numbers to generate" << endl << endl;

    int x_max,x0, k;
    cout << "x_max: ";
    cin >> x_max;
    cout << "k: ";
    do{
        cin >> k;
    }while(k <= 0);
    cout << endl;


    unsigned int mt_array[624];
    for(int i=0; i<624; ++i)
        mt_array[i] = rand();


    int counter = 0;
    for(int i=0; i<k; ++i)
    {
        long long r = random_Mersenne_Twister_19937(mt_array);
        cout << ++counter << ": " << r % (x_max + 1) << endl;
    }


    cout << endl;
    system("pause");
    return 0;
}
