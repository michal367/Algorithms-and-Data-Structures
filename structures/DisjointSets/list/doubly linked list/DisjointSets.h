#pragma once

#include <list>

template<class T>
class DisjointSets
{
    std::list<std::list<T> > sets;

public:
    DisjointSets() {};

    void makeSet(T element);
    void addElement(T element, T dest);
    bool include(T element);
    typename std::list<T>::iterator find(T element);
    typename std::list<T>::iterator findSet(T element);
    void unionSets(T element1, T element2);

    std::size_t size();
    std::list<T> getSet(std::size_t index);
    typename std::list<std::list<T> >::iterator findSet2(T element);

};



template<class T>
void DisjointSets<T>::makeSet(T element)
{
    if(!include(element))
    {
        sets.push_back(std::list<T>());
        sets.back().push_back(element);
    }
}

template<class T>
typename std::list<T>::iterator DisjointSets<T>::findSet(T element)
{
    typename std::list<std::list<T> >::iterator it1 = sets.begin();
    for(; it1 != sets.end(); ++it1)
        for(typename std::list<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
            if(*it2 == element)
                return it1->begin();
    return it1->end();
}

template<class T>
void DisjointSets<T>::unionSets(T element1, T element2)
{
    if(element1 != element2)
    {
        typename std::list<std::list<T> >::iterator it_first = findSet2(element1);
        if(it_first != sets.end())
        {
            typename std::list<std::list<T> >::iterator it_second = findSet2(element2);;
            if(it_second != sets.end() && it_first != it_second)
            {
                if(it_first->size() >= it_second->size())
                {
                    it_first->splice(it_first->end(), *it_second);
                    sets.erase(it_second);
                }
                else
                {
                    it_second->splice(it_second->end(), *it_first);
                    sets.erase(it_first);
                }
            }
        }
    }
}



template<class T>
void DisjointSets<T>::addElement(T element, T dest)
{
    if(!include(element))
    {
        for(typename std::list<std::list<T> >::iterator it1 = sets.begin(); it1 != sets.end(); ++it1)
            for(typename std::list<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
                if(*it2 == dest)
                    it1->push_back(element);
    }
}




template<class T>
bool DisjointSets<T>::include(T element)
{
    for(typename std::list<std::list<T> >::iterator it1 = sets.begin(); it1 != sets.end(); ++it1)
        for(typename std::list<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
            if(*it2 == element)
                return true;
    return false;
}
template<class T>
typename std::list<T>::iterator DisjointSets<T>::find(T element)
{
    for(typename std::list<std::list<T> >::iterator it1 = sets.begin(); it1 != sets.end(); ++it1)
        for(typename std::list<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
            if(*it2 == element)
                return it2;
    return nullptr;
}
template<class T>
typename std::list<std::list<T> >::iterator DisjointSets<T>::findSet2(T element)
{
    for(typename std::list<std::list<T> >::iterator it1 = sets.begin(); it1 != sets.end(); ++it1)
        for(typename std::list<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
            if(*it2 == element)
                return it1;
    return sets.end();
}





template<class T>
std::size_t DisjointSets<T>::size()
{
    return sets.size();
}
template<class T>
std::list<T> DisjointSets<T>::getSet(std::size_t index)
{
    typename std::list<std::list<T> >::iterator it = sets.begin();
    std::advance(it, index);
    return *it;
}
