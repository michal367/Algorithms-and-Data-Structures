#pragma once

#include <vector>

template <class T>
class Heap
{
    std::vector<T> heap;

public:
    Heap();
    Heap(T value);
    Heap(const Heap& other);
    Heap& operator=(const Heap& other);

    void push(T value);
    T pop();

    T getRootValue();

    size_t size();
    T at(size_t index);
    bool empty();
};


template <class T>
Heap<T>::Heap() {}

template <class T>
Heap<T>::Heap(T value)
{
    heap.push_back(value);
}

template <class T>
Heap<T>::Heap(const Heap& other)
{
    heap = other.heap;
}
template <class T>
Heap<T>& Heap<T>::operator=(const Heap& other)
{
    if(this != &other)
    {
        heap = other.heap;
    }
    return *this;
}


template <class T>
void Heap<T>::push(T value)
{
    heap.push_back(value);

    size_t k = heap.size() - 1;
    size_t k2 = size_t((k-1)/2);

    while(k > k2 && heap.at(k) > heap.at(k2))
    {
        T temp = heap.at(k);
        heap.at(k) = heap.at(k2);
        heap.at(k2) = temp;
        k = k2;
        k2 = size_t((k-1)/2);
    }
}

template <class T>
T Heap<T>::pop()
{
    if(heap.size() > 0)
    {
        T result = heap.front();

        size_t n = heap.size() - 1;
        size_t k = 0;
        heap.at(k) = heap.at(n);
        heap.pop_back();

        size_t kc = 1;

        while(kc < n)
        {
            if(kc+1 < n && heap.at(kc+1) > heap.at(kc))
                kc += 1;

            if(heap.at(kc) > heap.at(k))
            {
                T temp = heap.at(k);
                heap.at(k) = heap.at(kc);
                heap.at(kc) = temp;
            }

            k = kc;
            kc = 2*k + 1;
        }
        return result;
    }
}

template <class T>
T Heap<T>::getRootValue()
{
    return heap.front();
}

template <class T>
size_t Heap<T>::size()
{
    return heap.size();
}
template <class T>
T Heap<T>::at(size_t index)
{
    return heap.at(index);
}
template <class T>
bool Heap<T>::empty()
{
    return heap.empty();
}



