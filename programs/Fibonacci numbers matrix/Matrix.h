#pragma once

#include <stdexcept>

template<class T>
class Matrix
{
    std::size_t m,n;
    T* matrix;


public:
    Matrix();
    Matrix(std::size_t m, std::size_t n);
    Matrix(std::size_t m, std::size_t n, const T& value);
    Matrix(const Matrix<T>& other);
    Matrix<T>& operator=(const Matrix<T>& other);
    ~Matrix();


    void setValue(std::size_t i, std::size_t j, const T& value);
    T getValue(std::size_t i, std::size_t j);

    T& at(std::size_t i, std::size_t j);

    std::size_t sizeM();
    std::size_t sizeN();

    bool isSquare();

    void fill(const T& value);

    void add(const Matrix<T>& b);
    void transpose();
    void multiply(double scalar);
    void multiply(Matrix<T> b);
    void power(unsigned int k);
    void power2(unsigned int k);


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
bool Matrix<T>::isSquare()
{
    return (m == n);
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
