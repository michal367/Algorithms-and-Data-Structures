#pragma once


template<class T>
class Stack
{
    T* array;
    std::size_t max_size;
    std::size_t sptr;

public:
    Stack(std::size_t size);
    Stack(std::initializer_list<T> il);
    Stack(std::size_t size, std::initializer_list<T> il);
    Stack(const Stack<T>& other);
    Stack<T>& operator=(const Stack<T>& other);
    ~Stack();


    T& top();
    void push(T value);
    void pop();

    std::size_t getSize();
    std::size_t getMaxSize();

    bool empty();
    void clear();
};


template<class T>
Stack<T>::Stack(std::size_t size)
{
    max_size = size;
    array = new T[max_size];
    sptr = 0;
}
template<class T>
Stack<T>::Stack(std::initializer_list<T> il)
{
    max_size = il.size();
    sptr = max_size;
    array = new T[max_size];
    T* ptr = array;
    for(typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it, ++ptr)
        (*ptr) = (*it);
}
template<class T>
Stack<T>::Stack(std::size_t size, std::initializer_list<T> il)
{
    if(size >= il.size())
    {
        max_size = size;
        sptr = il.size();
        array = new T[max_size];
        T* ptr = array;
        for(typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it, ++ptr)
            (*ptr) = (*it);
    }
}
template<class T>
Stack<T>::Stack(const Stack<T>& other)
{
    max_size = other.max_size;
    sptr = other.sptr;
    array = new T[max_size];

    for(std::size_t i=0; i<max_size; ++i)
        array[i] = other.array[i];
}
template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if(this != &other)
    {
        if(!empty())
            delete[] array;

        max_size = other.max_size;
        sptr = other.sptr;
        array = new T[max_size];

        for(std::size_t i=0; i<max_size; ++i)
            array[i] = other.array[i];
    }
    return *this;
}
template<class T>
Stack<T>::~Stack()
{
    delete[] array;
    sptr = 0;
    max_size = 0;
}


template<class T>
std::size_t Stack<T>::getSize()
{
    return sptr;
}
template<class T>
std::size_t Stack<T>::getMaxSize()
{
    return max_size;
}



template<class T>
T& Stack<T>::top()
{
    if(!empty())
        return array[sptr-1];
}
template<class T>
void Stack<T>::push(T value)
{
    if(sptr != max_size)
    {
        array[sptr] = value;
        ++sptr;
    }
}
template<class T>
void Stack<T>::pop()
{
    if(!empty())
        --sptr;
}



template<class T>
bool Stack<T>::empty()
{
    return (sptr == 0);
}
template<class T>
void Stack<T>::clear()
{
    sptr = 0;
}
