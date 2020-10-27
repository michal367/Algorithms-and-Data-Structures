#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


typedef unsigned long long ulong;


int gcd(int a, int b)
{
    while(b != 0)
    {
        int temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}
long long modular_multiplicative_inverse(long long a, long long b)
{
    long long u = 1, w = a;
    long long x = 0, z = b;

    while(w != 0)
    {
        if(w < z)
        {
            swap(u,x);
            swap(w,z);
        }
        long long q = w/z;
        u -= q*x;
        w = w%z;
    }
    if(z == 1 && x < 0)
        x += b;

    return x;
}

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



int main()
{
    srand(time(NULL));

    cout << "RSA" << endl
         << "t - number to cipher" << endl << endl;

    int t;
    cout << "t: ";
    cin >> t;
    cout << endl;


    // ===================================

    const int first_primes_size = 169;
    const int first_primes[first_primes_size] = {
          2,  3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
         71, 73, 79, 83, 89, 97,101,103,107,109,113,127,131,137,139,149,151,157,163,
        167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,
        271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,
        389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,
        503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,
        631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,
        757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,
        883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009};

    int p,q;
    p = first_primes[rand() % first_primes_size];
    do{
        q = first_primes[rand() % first_primes_size];
    }while(p == q);


    int phi = (p-1)*(q-1);
    int n = p*q;

    int e;
    int coprime = gcd(2,phi);
    for(int i=3; coprime != 1 && i < n; ++i)
    {
        coprime = gcd(i,phi);
        e = i;
    }

    int d = modular_multiplicative_inverse(e, phi);


    cout << "Public key:" << endl
         << "public exponent: " << e << endl
         << "modulus: " << n << endl << endl;
    cout << "Private key:" << endl
         << "private exponent: " << d << endl
         << "modulus: " << n << endl << endl;
    cout << endl;


    // ===================================

    int c = power_modulo(t, e, n);
    cout << "Encrypted number: " << c << endl;

    c = power_modulo(c, d, n);
    cout << "Decrypted number: " << c << endl;


    cout << endl;
    system("pause");
    return 0;
}





