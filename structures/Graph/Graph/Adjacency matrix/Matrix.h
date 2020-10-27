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
    void clear();

    void removeRow(std::size_t row);
    void removeColumn(std::size_t column);

    void fill(const T& value);

    void add(const Matrix<T>& b);
    void transpose();
    void multiply(double scalar);
    void multiply(Matrix<T> b);
    void power(unsigned int k);
    void power2(unsigned int k);

    bool operator==(const Matrix<T>& other);

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
void Matrix<T>::clear(){
    delete[] matrix;
    m = n = 0;
}


template<class T>
void Matrix<T>::removeRow(std::size_t row){
    if(row >= 0 && row < m){
        T* new_matrix = new T[(m-1)*n];

        for(int i=0, i2=0; i<m-1; ++i, ++i2){
            if(i == row)
                i2++;
            for(int j=0; j<n; ++j)
                new_matrix[i*n + j] = matrix[i2*n + j];
        }

        delete[] matrix;

        m--;
        matrix = new_matrix;
    }
}

template<class T>
void Matrix<T>::removeColumn(std::size_t column){
    if(column >= 0 && column < n){
        T* new_matrix = new T[m*(n-1)];

        for(int i=0; i<m; i++)
            for(int j=0, j2=0; j<n-1; j++, j2++){
                if(j == column)
                    j2++;
                new_matrix[i*(n-1) + j] = matrix[i*n + j2];
            }

        delete[] matrix;

        n--;
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
bool Matrix<T>::operator==(const Matrix<T>& other){
    if(m != other.m || n != other.n)
        return false;

    for(int i=0; i < m; i++)
        for(int j=0; j < n; j++)
            if(matrix[i*n + j] != other.matrix[i*n + j])
                return false;
    return true;
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
