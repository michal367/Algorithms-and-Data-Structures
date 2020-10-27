#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void prime_factor_Fermat(unsigned long long n)
{
    unsigned long long x = ceil(sqrt(n));
    unsigned long long dx = 2*x+1;
    unsigned long long dy = 1;
    double e = x*x - n;
    //cout << "e: " << e << endl;

    while(e != 0)
    {
        while(e > 0)
        {
            e -= dy;
            dy += 2;
        }
        while(e < 0)
        {
            e += dx;
            dx += 2;
        }
        if((dx + dy)/2 > n)
        {
            dx = 2;
            dy = 0;
            break;
        }
    }
    unsigned long long m1 = (dx+dy)/2 - 1;
    unsigned long long m2 = (dx-dy)/2;
    if(m2 == 1)
    {
        cout << n << endl;
        return;
    }
    else
    {
        prime_factor_Fermat(m1);
        prime_factor_Fermat(m2);
        return;
    }
}

int main()
{
    cout << "Prime factors - Fermat's method" << endl;
    cout << "Decomposition of the number n into prime factors" << endl << endl;

    unsigned long long n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 2);


     const int first_primes[] = {
          2,  3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
         71, 73, 79, 83, 89, 97,101,103,107,109,113,127,131,137,139,149,151,157,163,
        167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,
        271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,
        389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,
        503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,
        631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,
        757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,
        883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009};


    cout << endl << "Prime factors:" << endl;
    unsigned long long m = n;
    for(const int* ptr=first_primes; ptr < first_primes+169 && m != 1; ++ptr)
    {
        while(m % (*ptr) == 0)
        {
            m /= (*ptr);
            cout << *ptr << endl;
        }
    }

    if(m > 1)
        prime_factor_Fermat(m);


    cout << endl;
    system("pause");
    return 0;
}


