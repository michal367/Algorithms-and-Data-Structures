#include <iostream>
#include <cstdlib>

#include "Matrix.h"

using namespace std;

string add(string a, string b)
{
    string result;

    int zeros;
    for(zeros=0; a[zeros] == '0'; ++zeros);
    a.erase(0,zeros);
    for(zeros=0; b[zeros] == '0'; ++zeros);
    b.erase(0,zeros);

    while(a.size() > b.size())
        b = '0' + b;
    while(b.size() > a.size())
        a = '0' + a;

    int move = 0;
    for(int i=a.size()-1, j=b.size()-1; i >= 0; --i, --j)
    {
        int res = a[i]-'0' + b[j]-'0' + move;
        move = 0;
        if(res >= 10)
        {
            move = res/10;
            res %= 10;
        }
        result = char(res+'0') + result;
    }
    if(move > 0)
        result = char(move+'0') + result;
    return result;
}

string multiply(string a, string b)
{
    string result;
    string z;
    for(int i=b.size()-1; i >= 0; --i)
    {
        string result2;

        string a2 = a;
        int b_digit = b[i]-'0';

        while(b_digit)
        {
            if(b_digit & 1)
                result2 = add(result2, a2);
            a2 = add(a2, a2);

            b_digit >>= 1;
        }
        result2.append(z);
        result = add(result, result2);
        z += '0';
    }
    return result;
}

template<>
void Matrix<std::string>::multiply(Matrix<std::string> b)
{
    if(n == b.m)
    {
        std::string* temp = new std::string[m * b.n];
        for(int i=0; i<m; ++i)
            for(int j=0; j<b.n; ++j)
            {
                std::string sum = "0";
                for(int k=0; k<n; ++k)
                    sum = ::add(sum, ::multiply(matrix[i*n + k], b.matrix[k*b.n + j]));
                temp[i*b.n + j] = sum;
            }
        delete[] matrix;
        n = b.n;
        matrix = temp;
    }
}
template<>
void Matrix<std::string>::power2(unsigned int k)
{
    if(isSquare())
    {
        if(k == 0)
        {
            for(int i=0; i<m; ++i)
                for(int j=0; j<n; ++j)
                    if(i == j)
                        matrix[i*n + j] = "1";
                    else
                        matrix[i*n + j] = "0";
        }
        else if(k > 1)
        {
            Matrix<std::string> result(this->m, this->n);
            for(int i=0; i<m; ++i)
                for(int j=0; j<n; ++j)
                {
                    if(i == j)
                        result.matrix[i*n + j] = "1";
                    else
                        result.matrix[i*n + j] = "0";
                }
            while(k)
            {
                if(k & 1)
                    result.multiply(*this);
                if(k >>= 1)
                    this->multiply(*this);
            }
            *this = result;
        }
    }
}

int main()
{
    cout << "Fibonacci numbers matrix" << endl
         << "n - n'th number" << endl << endl;

    int n;
    cout << "n: ";
    do{
        cin >> n;
    }while(n <= 0);
    cout << endl;

    Matrix<string> matrix(2,2);
    matrix.at(0,0) = "1";
    matrix.at(0,1) = "1";
    matrix.at(1,0) = "1";
    matrix.at(1,1) = "0";


    cout << matrix << endl;
    cout << "to the " << n-1 << " power =" << endl << endl;
    matrix.power2(n-1);
    cout << matrix << endl;
    cout << endl << "Result: " << matrix.at(0,0) << endl;


    cout << endl;
    system("pause");
    return 0;
}
