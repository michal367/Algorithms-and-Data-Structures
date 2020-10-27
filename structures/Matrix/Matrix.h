#pragma once

#include <stdexcept>

#include <iostream>

template<class T>
class Matrix
{
    // matrix with size m x n

    std::size_t m,n;
    T* matrix;


public:
    Matrix();
    Matrix(std::size_t m, std::size_t n);
    Matrix(std::size_t m, std::size_t n, const T& value);
    Matrix(std::size_t m, std::size_t n, std::initializer_list<T> il);
    Matrix(const Matrix<T>& other);
    Matrix<T>& operator=(const Matrix<T>& other);
    ~Matrix();


    void setValue(std::size_t i, std::size_t j, const T& value);
    T getValue(std::size_t i, std::size_t j);

    T& at(std::size_t i, std::size_t j);

    std::size_t sizeM();
    std::size_t sizeN();

    bool isSquare();

    void resize(std::size_t new_n, std::size_t new_m);

    void fill(const T& value);

    void add(const Matrix<T>& b);
    void transpose();
    void multiply(double scalar);
    void multiply(Matrix<T> b);
    void power(unsigned int k);
    void power2(unsigned int k);

    template<class T2>
    Matrix<T> eliminationGauss(Matrix<T2> results);
    template<class T2>
    Matrix<T> eliminationGaussCrout(Matrix<T2> results);

    T minor(std::size_t column, std::size_t row);
    T determinant();

    void LUdecomposition();
    void LUdecomposition2();
    template<class T2>
    Matrix<T> LUsolve(Matrix<T2> results);

    void LUinvert();
    T LUdeterminant();

    template<class T2>
    friend std::ostream& operator<< (std::ostream& os, const Matrix<T2>& m);
};





template<class T>
Matrix<T>::Matrix()
{
    m = n = 0;
    matrix = nullptr;
}
template<class T>
Matrix<T>::Matrix(std::size_t m, std::size_t n)
{
    this->m = m;
    this->n = n;
    matrix = new T[m*n];
}
template<class T>
Matrix<T>::Matrix(std::size_t m, std::size_t n, const T& value)
{
    this->m = m;
    this->n = n;
    matrix = new T[m*n];
    for(int i=0; i<m*n; ++i)
        matrix[i] = value;
}
template<class T>
Matrix<T>::Matrix(std::size_t m, std::size_t n, std::initializer_list<T> il)
{
    if(il.size() == m*n)
    {
        this->m = m;
        this->n = n;
        matrix = new T[m*n];
        const T* ptr = il.begin();
        for(T* ptr_m = matrix; ptr != il.end(); ++ptr, ++ptr_m)
            *ptr_m = *ptr;
    }
    else
        Matrix();
}
template<class T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
    m = other.m;
    n = other.n;
    matrix = new T[m*n];
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            matrix[i*n + j] = other.matrix[i*n + j];
}
template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
    if(this != &other)
    {
        if(matrix != nullptr)
            delete[] matrix;

        m = other.m;
        n = other.n;
        matrix = new T[m*n];
        for(int i=0; i<m; ++i)
            for(int j=0; j<n; ++j)
                matrix[i*n + j] = other.matrix[i*n + j];
    }
    return *this;
}

template<class T>
Matrix<T>::~Matrix()
{
    delete[] matrix;
}



template<class T>
void Matrix<T>::setValue(std::size_t i, std::size_t j, const T& value)
{
    if(i >= 0 && i < m && j >=0 && j < n)
        matrix[i*n + j] = value;
    else
        throw std::out_of_range("Matrix::setValue");
}
template<class T>
T Matrix<T>::getValue(std::size_t i, std::size_t j)
{
    if(i >= 0 && i < m && j >=0 && j < n)
        return matrix[i*n + j];
    else
        throw std::out_of_range("Matrix::getValue");
}

template<class T>
T& Matrix<T>::at(std::size_t i, std::size_t j)
{
    if(i >= 0 && i < m && j >=0 && j < n)
        return matrix[i*n + j];
    else
        throw std::out_of_range("Matrix::at");
}

template<class T>
std::size_t Matrix<T>::sizeM()
{
    return m;
}
template<class T>
std::size_t Matrix<T>::sizeN()
{
    return n;
}

template<class T>
void Matrix<T>::resize(std::size_t new_m, std::size_t new_n){
    if(new_n > 0 && new_m > 0){
        T* new_matrix = new T[new_m*new_n];

        std::size_t min_m = std::min(m, new_m);
        std::size_t min_n = std::min(n, new_n);

        /*for(int i=0; i<min_m; ++i)
            for(int j=0; j<min_n; ++j)
                new_matrix[i*new_n + j] = matrix[i*n + j];*/

        for(int i=0; i<new_m; ++i)
            for(int j=0; j<new_n; ++j){
                if(i < min_m && j < min_n)
                    new_matrix[i*new_n + j] = matrix[i*n + j];
                else
                    new_matrix[i*new_n + j] = T();
            }

        delete[] matrix;

        m = new_m;
        n = new_n;
        matrix = new_matrix;
    }
}


template<class T>
bool Matrix<T>::isSquare()
{
    return (m == n && m > 0);
}


template<class T>
void Matrix<T>::fill(const T& value)
{
    for(int i=0; i<m*n; ++i)
        matrix[i] = value;
}


template<class T>
void Matrix<T>::multiply(double scalar)
{
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            matrix[i*n + j] *= scalar;
}
template<class T>
void Matrix<T>::multiply(Matrix<T> b)
{
    if(n == b.m)
    {
        T* temp = new T[m * b.n];
        for(int i=0; i<m; ++i)
            for(int j=0; j<b.n; ++j)
            {
                T sum = 0;
                for(int k=0; k<n; ++k)
                    sum += matrix[i*n + k] * b.matrix[k*b.n + j];
                temp[i*b.n + j] = sum;
            }
        delete[] matrix;
        n = b.n;
        matrix = temp;
    }
}
template<class T>
void Matrix<T>::power(unsigned int k)
{
    if(isSquare())
    {
        if(k == 0)
        {
            for(int i=0; i<m; ++i)
                for(int j=0; j<n; ++j)
                    matrix[i*n + j] = 1;
        }
        else
        {
            Matrix<T> temp(*this);
            for(int i=1; i<k; ++i)
                multiply(temp);
        }
    }
}
template<class T>
void Matrix<T>::power2(unsigned int k)
{
    if(isSquare())
    {
        if(k == 0)
        {
            for(int i=0; i<m; ++i)
                for(int j=0; j<n; ++j)
                    matrix[i*n + j] = 1;
        }
        else if(k > 1)
        {
            Matrix<T> result(this->m, this->n);
            for(int i=0; i<m; ++i)
                for(int j=0; j<n; ++j)
                {
                    if(i == j)
                        result.matrix[i*n + j] = 1;
                    else
                        result.matrix[i*n + j] = 0;
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
template<class T>
void Matrix<T>::add(const Matrix<T>& b)
{
    if(m == b.m && n == b.n)
        for(int i=0; i<m; ++i)
            for(int j=0; j<n; ++j)
                matrix[i*n + j] += b.matrix[i*n + j];
}
template<class T>
void Matrix<T>::transpose()
{
    if(m == n)
    {
        for(int i=1; i<m; ++i)
            for(int j=0; j<i+1; ++j)
                std::swap(matrix[i*n + j], matrix[j*m + i]);
    }
    else
    {
        std::swap(m,n);
        T* temp = new T[m*n];
        for(int i=0; i<m; ++i)
            for(int j=0; j<n; ++j)
                temp[i*n + j] = matrix[j*m + i];

        delete[] matrix;
        matrix = temp;
    }
}


template<class T>
template<class T2>
Matrix<T> Matrix<T>::eliminationGauss(Matrix<T2> results)
{
    if(isSquare() && results.m == m && results.n == 1)
    {
        for(std::size_t i=1; i<m; ++i)
        {
            T2 nr = matrix[(i-1)*n + (i-1)];
            for(std::size_t j=i; j<m; ++j)
            {
                T2 nr2 = matrix[j*n + (i-1)] / nr;
                for(std::size_t k=i-1; k<n; ++k)
                {
                    if(k < i)
                        matrix[j*n + k] = 0;
                    else
                    {
                        T2 nr3 = matrix[(i-1)*n + k];
                        matrix[j*n + k] -= nr2 * nr3;
                    }
                }
                results.matrix[j] -= nr2 * results.matrix[i-1];
            }
        }


        for(std::size_t i=m-1; i<=m-1; --i)
        {
            for(std::size_t j=n-1; j>i; --j)
                results.matrix[i] -= matrix[i*n + j] * results.matrix[j];
            results.matrix[i] /= matrix[i*n + i];
        }
    }
    return results;
}

template<class T>
template<class T2>
Matrix<T> Matrix<T>::eliminationGaussCrout(Matrix<T2> results)
{
    if(isSquare() && results.m == m && results.n == 1)
    {
        std::size_t* pos = new std::size_t[n];
        for(std::size_t i=0; i < m; ++i)
            pos[i] = i;

        for(std::size_t i=0; i<m; ++i)
        {
            if(matrix[i*n + i] == 0)
            {
                T max = 0;
                std::size_t max_pos = 0;
                for(std::size_t j=0; j < n; ++j)
                    if(abs(matrix[i*n + pos[j]]) > max)
                    {
                        max = abs(matrix[i*n + pos[j]]);
                        max_pos = j;
                    }
                std::swap(pos[i], pos[max_pos]);
            }

            T2 nr = matrix[i*n + pos[i]];
            for(std::size_t j=i+1; j<m; ++j)
            {
                T2 nr2 = matrix[j*n + pos[i]] / nr;
                for(std::size_t k=i; k<n; ++k)
                {
                    T2 nr3 = matrix[i*n + pos[k]];
                    matrix[j*n + pos[k]] -= nr2 * nr3;
                }
                results.matrix[j] -= nr2 * results.matrix[i];
            }
        }

        for(std::size_t i=m-1; i<=m-1; --i)
        {
            for(std::size_t j=n-1; j>i; --j)
                results.matrix[i] -= matrix[i*n + pos[j]] * results.matrix[j];
            results.matrix[i] /= matrix[i*n + pos[i]];
        }

        for(std::size_t i=0; i<m; ++i)
            while(pos[i] != i)
            {
                std::swap(results.matrix[i], results.matrix[pos[i]]);
                std::swap(pos[i], pos[pos[i]]);
            }
        /*Matrix<T2> results2(results);
        for(std::size_t i=0; i<n; ++i)
            results2.at(pos[i],0) = results.at(i,0);*/

        delete[] pos;
        return results;
    }
}


template<class T>
T Matrix<T>::minor(std::size_t column, std::size_t row)
{
    if(isSquare() && column < m && row < n)
    {
        Matrix<T> result(m-1, n-1);
        for(std::size_t i=0, i2=0; i<m; ++i)
            if(i != column)
            {
                for(std::size_t j=0, j2=0; j<n; ++j)
                    if(j != row)
                    {
                        result.matrix[i2*(n-1) +j2] = matrix[i*n +j];
                        ++j2;
                    }
                ++i2;
            }
        return result.determinant();
    }
}


template<class T>
T Matrix<T>::determinant()
{
    if(isSquare())
    {
        if(m == 1)
            return matrix[0];
        else if(m == 2)
            return (matrix[0]*matrix[3] - matrix[1]*matrix[2]);
        else
        {
            T sum = 0;
            for(std::size_t i=0; i<n; ++i)
            {
                if(i%2 == 0)
                    sum += matrix[i] * minor(0,i);
                else
                    sum -= matrix[i] * minor(0,i);
            }
            return sum;
        }
    }
}


template<class T>
void Matrix<T>::LUdecomposition()
{
    if(isSquare())
    {
        for(std::size_t j = 0; j<n; ++j)
        {
            for(std::size_t i = 0; i<m; ++i)
            {
                T sum = 0;
                if(i <= j)
                {
                    for(std::size_t k=0; k<i; ++k)
                        sum += matrix[i*n + k] * matrix[k*n + j];
                    matrix[i*n + j] = matrix[i*n + j] - sum;
                }
                else
                {
                    for(std::size_t k=0; k<j; ++k)
                        sum += matrix[i*n + k] * matrix[k*n + j];
                    matrix[i*n + j] = (matrix[i*n + j] - sum) / matrix[j*n + j];
                }
            }
        }
    }
}
template<class T>
void Matrix<T>::LUdecomposition2()
{
    if(isSquare())
    {
        for(std::size_t k=0; k<m-1; ++k)
        {
            for(std::size_t i=k+1; i<m; ++i)
                matrix[i*n + k] /= matrix[k*n + k];

            for(std::size_t i=k+1; i<m; ++i)
                for(std::size_t j=k+1; j<n; ++j)
                    matrix[i*n + j] -= matrix[i*n + k] * matrix[k*n + j];
        }
    }
}

template<class T>
template<class T2>
Matrix<T> Matrix<T>::LUsolve(Matrix<T2> results)
{
    if(isSquare())
    {
        Matrix<T> LU(*this);
        LU.LUdecomposition2();

        for(std::size_t i=0; i<m; ++i)
            for(std::size_t j=0; j<i; ++j)
                results.matrix[i] -= LU.matrix[i*n + j] * results.matrix[j];
        for(std::size_t i=m-1; i<=m-1; --i)
        {
            for(std::size_t j=i+1; j<m; ++j)
                results.matrix[i] -= LU.matrix[i*n + j] * results.matrix[j];
            results.matrix[i] /= LU.matrix[i*n + i];
        }
        return results;
    }
}

template<class T>
void Matrix<T>::LUinvert()
{
    if(isSquare())
    {
        Matrix<T> LU(*this);
        LU.LUdecomposition2();

        for(std::size_t i=0; i<m; ++i)
            for(std::size_t j=0; j<n; ++j)
            {
                if(i != j)
                    matrix[i*n + j] = 0;
                else
                    matrix[i*n + j] = 1;
            }

        for(std::size_t a=0; a<n; ++a)
        {
            for(std::size_t i=0; i<m; ++i)
                for(std::size_t j=0; j<i; ++j)
                    matrix[i*n + a] -= LU.matrix[i*n + j] * matrix[j*n + a];
            for(std::size_t i=m-1; i<=m-1; --i)
            {
                for(std::size_t j=i+1; j<m; ++j)
                    matrix[i*n + a] -= LU.matrix[i*n + j] * matrix[j*n + a];
                matrix[i*n + a] /= LU.matrix[i*n + i];
            }
        }
    }
}
template<class T>
T Matrix<T>::LUdeterminant()
{
    if(isSquare())
    {
        Matrix<T> LU(*this);
        LU.LUdecomposition2();

        T result = 1;
        for(std::size_t i=0; i<m; ++i)
            result *= LU.matrix[i*n + i];

        return result;
    }
}




template<class T>
std::ostream& operator<< (std::ostream& os, const Matrix<T>& m)
{
    for(int i=0; i<m.m; i++)
    {
        os << "|";
        for(int j=0; j<m.n-1; j++)
            os << m.matrix[i*m.n + j] << ' ';
        os << m.matrix[i*m.n + m.n - 1];
        os << "|\n";
    }
    return os;
}
