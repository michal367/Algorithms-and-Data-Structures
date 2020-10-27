#pragma once

#include <stdexcept>
#include <iostream>

class Set{
    int min;
    int max;
    bool* values;

public:
    Set(int min, int max);
    Set(std::initializer_list<int> il);
    Set(const Set& other);
    Set& operator=(const Set& other);
    ~Set();

    int get_min();
    int get_max();
    std::size_t getsize();
    std::size_t getmaxsize();
    bool empty();
    void clear();

    void push(int value);
    void erase(int value);
    bool contains(int value);

    void sets_union(const Set& other);
    void intersection(const Set& other);
    void difference(const Set& other);
    void complement();

    bool is_subset(const Set& subset);


    friend std::ostream& operator<< (std::ostream& os, Set& set);
};




Set::Set(int min, int max){
    if(max >= min){
        this->min = min;
        this->max = max;
        std::size_t size = max - min + 1;
        values = new bool[size];
        for(int i=0; i<size; i++)
            values[i] = false;
    }
    else
        throw std::invalid_argument("min > max");
}
Set::Set(std::initializer_list<int> il){
    if(il.size() > 0){
        min = *il.begin();
        max = *il.begin();
        for(auto it = il.begin(); it != il.end(); it++){
            if(*it < min)
                min = *it;
            else if(*it > max)
                max = *it;
        }
        int size = max - min + 1;
        values = new bool[size];
        for(int i=0; i<size; i++)
            values[i] = false;

        for(auto it = il.begin(); it != il.end(); it++){
            int index = *it - min;
            values[index] = true;
        }
    }
    else
        throw std::invalid_argument("Size of initializer list is 0");
}

Set::Set(const Set& other){
    max = other.max;
    min = other.min;
    std::size_t size = max - min + 1;
    values = new bool[size];
    for(int i=0; i < size; i++)
        values[i] = other.values[i];
}
Set& Set::operator=(const Set& other){
    if(this != &other){
        delete[] values;

        max = other.max;
        min = other.min;
        std::size_t size = max - min + 1;
        values = new bool[size];
        for(int i=0; i < size; i++)
            values[i] = other.values[i];
    }
    return *this;
}

Set::~Set(){
    delete[] values;
}


int Set::get_min(){
    return min;
}
int Set::get_max(){
    return max;
}

std::size_t Set::getsize(){
    std::size_t counter = 0;
    for(int i=0; i < max-min + 1; i++)
        if(values[i])
            counter++;
    return counter;
}
std::size_t Set::getmaxsize(){
    return (max - min + 1);
}
bool Set::empty(){
    return (getsize() == 0);
}
void Set::clear(){
    for(int i=0; i < max-min + 1; i++)
        values[i] = false;
}


void Set::push(int value){
    if(value >= min && value <= max){
        int index = value - min;
        values[index] = true;
    }
}
void Set::erase(int value){
    if(value >= min && value <= max){
        int index = value - min;
        values[index] = false;
    }
}
bool Set::contains(int value){
    if(value >= min && value <= max){
        int index = value - min;
        return values[index];
    }
    return false;
}





void Set::sets_union(const Set& other){
    int new_min = std::min(min, other.min);
    int new_max = std::max(max, other.max);
    int new_size = new_max - new_min + 1;
    bool* new_values = new bool[new_size];
    for(int i=0; i<new_size; i++)
        new_values[i] = false;

    for(int i=0; i < max-min+1; i++)
        if(values[i])
            new_values[i - (new_min - min)] = true;

    for(int i=0; i < other.max - other.min + 1; i++)
        if(other.values[i])
            new_values[i - (new_min - other.min)] = true;

    min = new_min;
    max = new_max;
    delete[] values;
    values = new_values;
}
void Set::intersection(const Set& other){
    bool* new_values = new bool[max-min+1];
    for(int i=0; i<max-min+1; i++)
        new_values[i] = false;

    for(int i=0; i < other.max - other.min + 1; i++)
        if(other.values[i] && values[i - (min - other.min)])
            new_values[i - (min - other.min)] = true;

    delete[] values;
    values = new_values;
}
void Set::difference(const Set& other){
    for(int i=0; i < other.max - other.min + 1; i++)
        if(other.values[i])
            values[i - (min - other.min)] = false;
}
void Set::complement(){
    for(int i=0; i<max - min + 1; i++)
        values[i] = !values[i];
}

bool Set::is_subset(const Set& subset){
    if(subset.min >= min && subset.max <= max){
        for(int i=0; i < subset.max - subset.min + 1; i++)
            if(values[i - (min - subset.min)] == false && subset.values[i] == true)
                return false;
        return true;
    }
    return false;
}




std::ostream& operator<< (std::ostream& os, Set& set)
{
    std::size_t size = set.getmaxsize();
    for(int i=0; i < size; i++)
        if(set.values[i])
            os << set.min+i << ' ';
    os << std::endl;
    return os;
}



