#pragma once

#include "SinglyLinkedCyclicList.h"

template<class T>
class Queue
{
    SinglyLinkedCyclicList<T> q;
public:
    Queue();
    Queue(std::initializer_list<T> il);
    Queue(const Queue<T>& other);
    Queue<T>& operator=(const Queue<T>& other);


    std::size_t getSize();

    T front();
    void push(const T val);
    void pop();

    bool empty();
    void clear();
};


template<class T>
Queue<T>::Queue() {}
template<class T>
Queue<T>::Queue(std::initializer_list<T> il)
{
    for(typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it)
        q.push_back(*it);
}
template<class T>
Queue<T>::Queue(const Queue<T>& other)
{
    q = other.q;
}
template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if(this != &other)
        q = other.q;
    return *this;
}



template<class T>
std::size_t Queue<T>::getSize()
{
    return q.get_size();
}

template<class T>
T Queue<T>::front()
{
    return q.front();
}
template<class T>
void Queue<T>::push(const T val)
{
    q.push_back(val);
}
template<class T>
void Queue<T>::pop()
{
    q.pop_front();
}

template<class T>
bool Queue<T>::empty()
{
    return q.empty();
}
template<class T>
void Queue<T>::clear()
{
    q.clear();
}
