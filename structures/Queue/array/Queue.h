#pragma once


template <class T>
class Queue
{
    T* array;
    std::size_t max_size;
    std::size_t size;
    std::size_t qptr;

public:
    Queue(std::size_t size);
    Queue(std::size_t size, std::initializer_list<T> il);
    Queue(std::initializer_list<T> il);
    Queue(const Queue<T>& other);
    Queue<T>& operator=(const Queue<T>& other);
    ~Queue();


    std::size_t getSize();
    std::size_t getMaxSize();

    T front();
    void push(const T val);
    void pop();

    bool empty();
    void clear();
};


template <class T>
Queue<T>::Queue(std::size_t size)
{
    this->max_size = size;
    array = new T[size];
    this->size = 0;
    this->qptr = 0;
}
template <class T>
Queue<T>::Queue(std::size_t size, std::initializer_list<T> il)
{
    this->max_size = size;
    this->size = std::min(size, il.size());
    qptr = 0;
    array = new T[size];
    std::size_t i = 0;
    for(typename std::initializer_list<T>::iterator it = il.begin(); it != il.end() && i < size; ++it, ++i)
        array[i] = *it;
}
template <class T>
Queue<T>::Queue(std::initializer_list<T> il)
{
    max_size = size = il.size();
    qptr = 0;
    array = new T[max_size];
    T* ptr = array;
    for(typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it, ++ptr)
        (*ptr) = (*it);
}

template <class T>
Queue<T>::Queue(const Queue<T>& other)
{
    max_size = other.max_size;
    size = other.size;
    array = new T[max_size];
    qptr = 0;
    T* ptr = array;
    for(std::size_t i = 0, j = other.qptr; i < other.size; ++i, ++ptr, j=(j+1)%max_size)
        (*ptr) = other.array[j];
}
template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if(this != &other)
    {
        if(!this->empty())
            delete[] array;
        max_size = other.max_size;
        size = other.size;
        array = new T[max_size];
        qptr = 0;
        T* ptr = array;
        for(std::size_t i = 0, j = other.qptr; i < other.size; ++i, ++ptr, j=(j+1)%max_size)
            (*ptr) = other.array[j];
    }
    return *this;
}


template <class T>
Queue<T>::~Queue()
{
    delete[] array;
    size = max_size = qptr = 0;
}




template <class T>
std::size_t Queue<T>::getSize()
{
    return size;
}
template <class T>
std::size_t Queue<T>::getMaxSize()
{
    return max_size;
}
template <class T>
bool Queue<T>::empty()
{
    return (size == 0);
}
template <class T>
T Queue<T>::front()
{
    if(size > 0)
        return array[qptr];
}
template <class T>
void Queue<T>::push(const T val)
{
    if(size < max_size)
    {
        array[(qptr+size) % max_size] = val;
        ++size;
    }
}
template <class T>
void Queue<T>::pop()
{
    if(size > 0)
    {
        ++qptr;
        --size;
        if(qptr == max_size)
            qptr = 0;
    }
}
template <class T>
void Queue<T>::clear()
{
    size = qptr = 0;
}
