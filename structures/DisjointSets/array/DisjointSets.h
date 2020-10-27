#pragma once

#include <vector>

template <class T>
class DisjointSets
{
    std::vector<T> elements;
    std::vector<T> representatives;

public:
    DisjointSets() {};


    void addElement(const T element, const T set);
    void addSet(const T set);
    T find(const T element);
    bool include(const T element, const T set);
    bool include(const T element);
    bool isSet(const T elements);
    void unionSets(const T set1, const T set2);

    std::size_t size();
    T getElement(std::size_t index);
    T getSetOfElement(std::size_t index);
    std::size_t getIndex(const T element);

};


template <class T>
void DisjointSets<T>::addElement(const T element, const T set)
{
    if(!include(element) && include(set))
    {
        elements.push_back(element);
        representatives.push_back(find(set));
    }
}

template <class T>
void DisjointSets<T>::addSet(const T set)
{
    if(!include(set))
    {
        elements.push_back(set);
        representatives.push_back(set);
    }
}

template <class T>
T DisjointSets<T>::find(const T element)
{
    typename std::vector<T>::iterator it = elements.begin();
    for(int i = 0; it != elements.end(); ++it, ++i)
        if(*it == element)
            return representatives.at(i);
    //return T();
}

template <class T>
bool DisjointSets<T>::include(const T element, const T set)
{
    return (find(element) == set);
}

template <class T>
bool DisjointSets<T>::include(const T element)
{
    typename std::vector<T>::iterator it = elements.begin();
    for(int i = 0; it != elements.end(); ++it)
        if(*it == element)
            return true;
    return false;
}

template <class T>
void DisjointSets<T>::unionSets(const T set1, const T set2)
{
    T x = find(set1);
    T y = find(set2);
    if(x != y)
    {
        typename std::vector<T>::iterator it = representatives.begin();
        for(; it != representatives.end(); ++it)
            if(*it == y)
                *it = x;
    }
}


template <class T>
std::size_t DisjointSets<T>::size()
{
    return elements.size();
}

template <class T>
T DisjointSets<T>::getElement(std::size_t index)
{
    return elements.at(index);
}

template <class T>
T DisjointSets<T>::getSetOfElement(std::size_t index)
{
    return representatives.at(index);
}

template <class T>
std::size_t DisjointSets<T>::getIndex(const T element)
{
    typename std::vector<T>::iterator it = elements.begin();
    for(int i = 0; it != elements.end(); ++it)
        if(*it == element)
            return i;
    return -1;
}
