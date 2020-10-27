#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <limits>

template<class T>
class Vector
{
    std::size_t size;
    std::size_t reserved;
    T* vec;
public:
    Vector();
    explicit Vector(std::size_t n);
    explicit Vector(std::size_t n, const T& val);
    Vector(const Vector<T>& other);
    Vector<T>& operator=(const Vector<T>& other);
    ~Vector();

    void reserve(std::size_t n);
    void resize(std::size_t n);

    T& at(std::size_t n);
    T& operator[](std::size_t n);
    T& front();
    T& back();

    void push_back(const T& val);
    void pop_back();

    void insert(std::size_t n, const T& val);

    std::size_t get_size();
    std::size_t get_reserved();
    std::size_t max_size();

    void erase(std::size_t n);
    void clear();
};

template<class T>
Vector<T>::Vector() :size(0), reserved(0), vec(NULL) {}

template<class T>
Vector<T>::Vector(std::size_t n) :size(n), reserved(n), vec(reinterpret_cast<T*>(::operator new(n*sizeof(T))))
{
    for(T* p=vec; p != vec+n; ++p)
        new(p) T();
}

template<class T>
Vector<T>::Vector(std::size_t n, const T& val) :size(n), reserved(n), vec(reinterpret_cast<T*>(::operator new(n*sizeof(T))))
{
    for(T* p=vec; p != vec+n; ++p)
        new(p) T(val);
}

template<class T>
Vector<T>::Vector(const Vector<T>& other)
{
    size = other.size;
    reserved = other.reserved;

    vec = reinterpret_cast<T*>(::operator new(reserved*sizeof(T)));
    for(int i=0; i<size; i++)
        vec[i] = other.vec[i];
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if(this != &other)
    {
        size = other.size;
        reserved = other.reserved;

        vec = reinterpret_cast<T*>(::operator new(reserved*sizeof(T)));
        for(int i=0; i<size; i++)
            vec[i] = other.vec[i];
    }
    return *this;
}

template<class T>
Vector<T>::~Vector()
{
    for(T* p=vec; p < vec+size; ++p)
        p->~T();
    ::operator delete(vec);
}

template<class T>
void Vector<T>::reserve(std::size_t n)
{
    if(n > max_size())
        throw std::length_error("Vector: length_error (n > max_size())");
    if(n > reserved)
    {
        reserved = n;
        T* temp_vec = reinterpret_cast<T*>(::operator new(n*sizeof(T)));
        for(int i=0; i<size; i++)
            *(temp_vec+i) = *(vec+i);

        for(T* p=vec; p<vec+size; ++p)
            p->~T();
        ::operator delete(vec);

        vec = temp_vec;
    }
}
template<class T>
void Vector<T>::resize(std::size_t n)
{
    if(n > max_size())
        throw std::length_error("Vector: length_error (n > max_size())");
    if(n != size)
    {
        if(n > reserved)
            reserve(n);
        if(n > size)
            for(T* p=vec+size; p != vec+n; ++p)
                new(p) T();
        else if(n < size)
            for(T* p=vec+n; p != vec+size; ++p)
                p->~T();

        size = n;
    }
}

template<class T>
T& Vector<T>::at(std::size_t n)
{
    if(n >= size)
        throw std::out_of_range("Vector: out_of_range (n >= size)");
    return *(vec+n);
}
template<class T>
T& Vector<T>::operator[](std::size_t n)
{
    if(n >= size)
        throw std::out_of_range("Vector: out_of_range (n >= size)");
    return *(vec+n);
}
template<class T>
T& Vector<T>::front()
{
    if(size == 0)
        throw std::out_of_range("Vector: out_of_range (size == 0)");
    return *vec;
}
template<class T>
T& Vector<T>::back()
{
    if(size == 0)
        throw std::out_of_range("Vector: out_of_range (size == 0)");
    return *(vec+size-1);
}

template<class T>
void Vector<T>::push_back(const T& val)
{
    if(reserved == 0)
        reserve(1);
    if(size+1 > reserved)
        reserve(2*reserved);

    new(vec+size) T(val);

    ++size;
}
template<class T>
void Vector<T>::pop_back()
{
    if(size > 0)
    {
        (vec+size-1)->~T();
        --size;
    }
}

template<class T>
void Vector<T>::insert(std::size_t n, const T& val)
{
    if(n >= size)
        throw std::out_of_range("Vector: out_of_range (n >= size)");
    if(n < size)
    {
        if(size+1 > reserved)
            reserve(2*reserved);
        for(T*p = vec+size-1; p != vec+n; --p)
            *p = *(p-1);
        (vec+n)->~T();
        new(vec+n) T(val);

        ++size;
    }
}

template<class T>
std::size_t Vector<T>::get_size() {return size;}
template<class T>
std::size_t Vector<T>::get_reserved() {return reserved;}
template<class T>
std::size_t Vector<T>::max_size() {return std::numeric_limits<size_t>::max() / sizeof(T);}

template<class T>
void Vector<T>::erase(std::size_t n)
{
    if(n >= size)
        throw std::out_of_range("Vector: out_of_range (n >= size)");
    if(n < size)
    {
        for(T* p=vec+n; p != vec+size-1; ++p)
            *p = *(p+1);
        (vec+size-1)->~T();

        --size;
    }
}
template<class T>
void Vector<T>::clear()
{
    for(T* p=vec; p != vec+size; ++p)
        p->~T();

    size = 0;
}


#endif // VECTOR_H
