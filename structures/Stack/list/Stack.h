#pragma once

#include <list>

template<class T>
class Stack
{
    std::list<T> st;

public:
    Stack();
    Stack(std::initializer_list<T> il);
    Stack(const Stack<T>& other);
    Stack<T>& operator=(const Stack<T>& other);

    T& top();
    void push(T value);
    void pop();

    std::size_t getSize();

    bool empty();
    void clear();
};



template<class T>
Stack<T>::Stack() {}
template<class T>
Stack<T>::Stack(std::initializer_list<T> il)
{
    for(typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it)
        st.push_back(*it);
}
template<class T>
Stack<T>::Stack(const Stack<T>& other)
{
    st = other.st;
}
template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if(this != &other)
        st = other.st;
    return *this;
}


template<class T>
std::size_t Stack<T>::getSize()
{
    return st.size();
}



template<class T>
T& Stack<T>::top()
{
    if(!empty())
        return st.back();
}
template<class T>
void Stack<T>::push(T value)
{
    st.push_back(value);
}
template<class T>
void Stack<T>::pop()
{
    if(!empty())
        st.pop_back();
}



template<class T>
bool Stack<T>::empty()
{
    return st.empty();
}
template<class T>
void Stack<T>::clear()
{
    st.clear();
}
