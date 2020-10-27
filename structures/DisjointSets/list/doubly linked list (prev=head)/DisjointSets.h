#pragma once

#include <vector>
#include "DisjointSetsList.h"

template<class T>
class DisjointSets
{
    std::vector<DisjointSetsList<T> > sets;

public:
    DisjointSets() {};

    void makeSet(T element);
    void addElement(T element, T dest);
    bool include(T element);
    typename DisjointSetsList<T>::iterator find(T element);
    typename DisjointSetsList<T>::iterator findSet(T element);
    void unionSets(T element1, T element2);

    void makeSet(typename DisjointSetsList<T>::iterator element);
    typename DisjointSetsList<T>::iterator findSet(typename DisjointSetsList<T>::iterator element);
    void unionSets(typename DisjointSetsList<T>::iterator element1, typename DisjointSetsList<T>::iterator element2);

    std::size_t size();
    DisjointSetsList<T> getSet(std::size_t index);
    typename std::vector<DisjointSetsList<T> >::iterator findSet2(T element);
    typename std::vector<DisjointSetsList<T> >::iterator findSet2(typename DisjointSetsList<T>::iterator element);

};



template<class T>
void DisjointSets<T>::makeSet(T element)
{
    if(!include(element))
    {
        sets.push_back(DisjointSetsList<T>());
        sets.back().push_back(element);
    }
}

template<class T>
typename DisjointSetsList<T>::iterator DisjointSets<T>::findSet(T element)
{
    typename std::vector<DisjointSetsList<T> >::iterator it1 = sets.begin();
    for(; it1 != sets.end(); ++it1)
        for(typename DisjointSetsList<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
            if(*it2 == element)
                return it1->begin();
    return it1->end();
}

template<class T>
void DisjointSets<T>::unionSets(T element1, T element2)
{
    if(element1 != element2)
    {
        typename std::vector<DisjointSetsList<T> >::iterator it_first = findSet2(element1);
        if(it_first != sets.end())
        {
            typename std::vector<DisjointSetsList<T> >::iterator it_second = findSet2(element2);
            if(it_second != sets.end() && it_first != it_second)
            {
                if(it_first->get_size() >= it_second->get_size())
                {
                    it_first->splice_list(*it_second);
                    sets.erase(it_second);
                }
                else
                {
                    it_second->splice_list(*it_first);
                    sets.erase(it_first);
                }
            }
        }
    }
}


template<class T>
typename DisjointSetsList<T>::iterator DisjointSets<T>::findSet(typename DisjointSetsList<T>::iterator element)
{
    return --element;
}
template<class T>
void DisjointSets<T>::unionSets(typename DisjointSetsList<T>::iterator element1, typename DisjointSetsList<T>::iterator element2)
{
    typename std::vector<DisjointSetsList<T> >::iterator it_first = findSet2(--element1);
    typename std::vector<DisjointSetsList<T> >::iterator it_second = findSet2(--element2);

    if(it_first != sets.end() && it_second != sets.end() && it_first != it_second)
    {
        if(it_first->get_size() >= it_second->get_size())
        {
            it_first->splice_list(*it_second);
            sets.erase(it_second);
        }
        else
        {
            it_second->splice_list(*it_first);
            sets.erase(it_first);
        }
    }
}





template<class T>
void DisjointSets<T>::addElement(T element, T dest)
{
    if(!include(element))
    {
        for(typename std::vector<DisjointSetsList<T> >::iterator it1 = sets.begin(); it1 != sets.end(); ++it1)
            for(typename DisjointSetsList<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
                if(*it2 == dest)
                    it1->push_back(element);
    }
}




template<class T>
bool DisjointSets<T>::include(T element)
{
    for(typename std::vector<DisjointSetsList<T> >::iterator it1 = sets.begin(); it1 != sets.end(); ++it1)
        for(typename DisjointSetsList<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
            if(*it2 == element)
                return true;
    return false;
}
template<class T>
typename DisjointSetsList<T>::iterator DisjointSets<T>::find(T element)
{
    for(typename std::vector<DisjointSetsList<T> >::iterator it1 = sets.begin(); it1 != sets.end(); ++it1)
        for(typename DisjointSetsList<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
            if(*it2 == element)
                return it2;
    return nullptr;
}
template<class T>
typename std::vector<DisjointSetsList<T> >::iterator DisjointSets<T>::findSet2(T element)
{
    for(typename std::vector<DisjointSetsList<T> >::iterator it1 = sets.begin(); it1 != sets.end(); ++it1)
        for(typename DisjointSetsList<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
            if(*it2 == element)
                return it1;
    return sets.end();
}
template<class T>
typename std::vector<DisjointSetsList<T> >::iterator DisjointSets<T>::findSet2(typename DisjointSetsList<T>::iterator element)
{
    for(typename std::vector<DisjointSetsList<T> >::iterator it1 = sets.begin(); it1 != sets.end(); ++it1)
        for(typename DisjointSetsList<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
            if(it2 == element)
                return it1;
    return sets.end();
}





template<class T>
std::size_t DisjointSets<T>::size()
{
    return sets.size();
}
template<class T>
DisjointSetsList<T> DisjointSets<T>::getSet(std::size_t index)
{
    return sets.at(index);
}
