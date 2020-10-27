#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef unsigned long long ulong;

ulong multiply_modulo(ulong a, ulong b, ulong n)
{
    ulong sum = 0;
    while(b != 0)
    {
        if(b & 1)
            sum = (sum + a) % n;
        a = (2*a) % n;
        b = b >> 1;
    }
    return sum;
}

ulong power_modulo(ulong a, ulong e, ulong n)
{
    ulong product = 1;
    ulong mod = a%n;
    if(e & 1)
        product = (product * mod) % n;
    e = e >> 1;
    while(e != 0)
    {
        mod = multiply_modulo(mod,mod, n);
        if(e & 1)
            product = multiply_modulo(product,mod, n);
        e = e >> 1;
    }
    return product;
}

ulong NWD(ulong a, ulong b)
{
    while(b != 0)
    {
        ulong temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}


int main()
{
    srand(time(NULL));

    cout << "Fermat's little theorem" << endl;
    cout << "Checking if a natural number n is prime with high probability" << endl << endl;

    ulong n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n < 2);
    cout << endl;

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

    bool is_prime = true;
    for(const int* ptr = first_primes; ptr != (first_primes+169); ++ptr)
    {
        if(n != (*ptr) && n%(*ptr) == 0)
        {
            is_prime = false;
            break;
        }
    }
    if(is_prime && n > 1009)
    {
        bool is_prime = true;
        for(int i=0; i<10; ++i)
        {
            ulong a = rand()%(n-1 -2 +1) + 2;
            //cout << "a: " << a << endl;

            if(NWD(n, a) != 1 || power_modulo(a,n-1, n) != 1)
            {
                is_prime = false;
                break;
            }
        }
    }
    if(is_prime)
        cout << "Number " << n << " is prime or is with a low probability Carmichael's pseudoprime" << endl;
    else
        cout << "Number " << n << " is NOT prime" << endl;

    cout << endl;
    system("pause");
    return 0;
}



