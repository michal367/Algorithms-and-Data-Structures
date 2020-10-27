#pragma once

#include <list>

template <class T>
class Set
{
    std::list<T> set_list;

public:
    Set(){}
    Set(std::initializer_list<T> il);
    Set(const Set<T>& other);
    Set<T>& operator=(const Set<T>& other);

    typename std::list<T>::iterator begin(){return set_list.begin();}
    typename std::list<T>::iterator end(){return set_list.end();}


    std::size_t getsize();
    bool empty();
    void clear();

    void push(T value);
    void erase(T value);
    bool contains(T value);

    void sets_union(const Set<T>& other);
    void intersection(const Set<T>& other);
    void difference(const Set<T>& other);

    bool is_subset(const Set<T>& subset);


};

template<class T>
Set<T>::Set(std::initializer_list<T> il){
    for(auto it = il.begin(); it != il.end(); ++it)
        if(!contains(*it))
            set_list.push_back(*it);
}
template<class T>
Set<T>::Set(const Set<T>& other){
    set_list = other.set_list;
}
template<class T>
Set<T>& Set<T>::operator=(const Set<T>& other){
    if(this != &other){
        set_list = other.set_list;
    }
    return *this;
}


template<class T>
std::size_t Set<T>::getsize(){
    return set_list.size();
}

template<class T>
bool Set<T>::empty(){
    return set_list.empty();
}

template<class T>
void Set<T>::clear(){
    set_list.clear();
}


template<class T>
void Set<T>::push(T value){
    if(!contains(value))
        set_list.push_back(value);
}

template<class T>
void Set<T>::erase(T value){
    for(auto it = set_list.begin(); it != set_list.end(); it++)
        if(*it == value){
            set_list.erase(it);
            return;
        }
}

template<class T>
bool Set<T>::contains(T value){
    for(auto it = set_list.begin(); it != set_list.end(); it++)
        if(*it == value)
            return true;
    return false;
}



template<class T>
void Set<T>::sets_union(const Set<T>& other){
    for(auto it = other.set_list.begin(); it != other.set_list.end(); it++)
        push(*it);
}

template<class T>
void Set<T>::intersection(const Set<T>& other){
    std::list<T> new_set;

    for(auto it = other.set_list.begin(); it != other.set_list.end(); it++){
        if(contains(*it))
            new_set.push_back(*it);
    }
    set_list = new_set;
}

template<class T>
void Set<T>::difference(const Set<T>& other){
    for(auto it = other.set_list.begin(); it != other.set_list.end(); it++){
        if(contains(*it))
            erase(*it);
    }
}

template<class T>
bool Set<T>::is_subset(const Set<T>& subset){
    for(auto it = subset.set_list.begin(); it != subset.set_list.end(); it++)
        if(!contains(*it))
            return false;
    return true;
}


