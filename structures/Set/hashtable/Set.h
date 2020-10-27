#pragma once

#include <iostream>
#include <stdexcept>

class Set{
    // set - hashtable - open addressing

    enum State{
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Slot{
        int value;
        State state;
    };

    std::size_t size;
    std::size_t max_size;
    Slot* table;

public:
    Set(std::size_t max_size);
    Set(std::size_t max_size, std::initializer_list<int> il);
    Set(const Set& other);
    Set& operator=(const Set& other);
    ~Set();

    std::size_t getsize();
    std::size_t getmaxsize();
    bool empty();
    void clear();

    void push(int value);
    void erase(int value);
    bool contains(int value) const;

    void sets_union(const Set& other);
    void intersection(const Set& other);
    void difference(const Set& other);

    bool is_subset(const Set& subset);

    friend std::ostream& operator<< (std::ostream& os, Set& set);

private:
    std::size_t hash(int value) const;
};


Set::Set(std::size_t max_size) : size(0) {
    this->max_size = max_size;
    table = new Slot[max_size];
    for(int i=0; i < max_size; i++)
        table[i].state = EMPTY;
}
Set::Set(std::size_t max_size, std::initializer_list<int> il) : Set(max_size) {
    if(il.size() <= max_size){
        for(auto it = il.begin(); it != il.end(); it++)
            push(*it);
    }
    else
        throw std::invalid_argument("Size of initializer list is greater than max_size");
}
Set::Set(const Set& other){
    size = other.size;
    max_size = other.max_size;
    table = new Slot[max_size];
    for(int i=0; i<max_size; i++)
        table[i] = other.table[i];
}
Set& Set::operator=(const Set& other){
    if(this != &other){
        delete[] table;

        size = other.size;
        max_size = other.max_size;
        table = new Slot[max_size];
        for(int i=0; i<max_size; i++)
            table[i] = other.table[i];
    }
    return *this;
}
Set::~Set(){
    delete[] table;
}

std::size_t Set::hash(int value) const{
    return value % max_size;
}


std::size_t Set::getsize(){
    return size;
}
std::size_t Set::getmaxsize(){
    return max_size;
}
bool Set::empty(){
    return (size == 0);
}
void Set::clear(){
    for(int i=0; i < max_size; i++)
        table[i].state = EMPTY;
    size = 0;
}




void Set::push(int value){
    if(size < max_size){
        std::size_t index = hash(value);

        while(table[index].state == OCCUPIED){
            if(table[index].value == value)
                return;
            index = (index+1)%max_size;
        }

        table[index].value = value;
        table[index].state = OCCUPIED;
        size++;
    }
    else
        throw std::invalid_argument("There are no empty place in set");
}
void Set::erase(int value){
    std::size_t index = hash(value);

    int i=0;
    while(i != max_size && table[index].state != EMPTY){
        if(table[index].value == value)
            break;
        else{
            index = (index+1)%max_size;
            i++;
        }
    }

    if(table[index].state == OCCUPIED && i != max_size){
        table[index].state = DELETED;
        size--;
    }
}
bool Set::contains(int value) const{
    std::size_t index = hash(value);

    int i=0;
    while(i != max_size && table[index].state != EMPTY){
        if(table[index].value == value)
            break;
        else{
            index = (index+1)%max_size;
            i++;
        }
    }

    if(table[index].state == OCCUPIED && i != max_size)
        return true;
    else
        return false;
}






void Set::sets_union(const Set& other){
    for(int i=0; i < other.max_size; i++){
        if(other.table[i].state == OCCUPIED)
            push(other.table[i].value);
    }
}
void Set::intersection(const Set& other){
    for(int i=0; i<max_size; i++){
        if(table[i].state == OCCUPIED && !other.contains(table[i].value))
            erase(table[i].value);
    }
}
void Set::difference(const Set& other){
    for(int i=0; i < other.max_size; i++){
        if(other.table[i].state == OCCUPIED)
            erase(other.table[i].value);
    }
}

bool Set::is_subset(const Set& subset){
    for(int i=0; i < subset.max_size; i++){
        if(subset.table[i].state == OCCUPIED && !contains(subset.table[i].value))
            return false;
    }
    return true;
}





std::ostream& operator<< (std::ostream& os, Set& set)
{
    for(int i=0; i < set.max_size; i++){
        if(set.table[i].state == set.EMPTY)
            os << i << ": EMPTY" << std::endl;
        else if(set.table[i].state == set.DELETED)
            os << i << ": DELETED" << std::endl;
        else
            os << i << ": " << set.table[i].value << std::endl;
    }
    return os;
}
