#pragma once

#include <stdexcept>
#include <iostream>
#include <bitset>

class Set{
    int min_value;
    std::size_t size;
    std::size_t max_size;
    std::size_t bytes_amount;
    unsigned int* values;

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
    bool contains(int value) const;

    void sets_union(const Set& other);
    void intersection(const Set& other);
    void difference(const Set& other);
    void complement();

    bool is_subset(const Set& subset);


    friend std::ostream& operator<< (std::ostream& os, const Set& set);
};


Set::Set(int min, int max) : min_value(min), size(0), max_size(max-min+1) {
    bytes_amount = ((max_size - 1) >> 5) + 1;
    values = new unsigned int[bytes_amount];
    for(int i=0; i<bytes_amount; i++)
        values[i] = 0;
}
Set::Set(std::initializer_list<int> il){
    if(il.size() > 0){
        min_value = *il.begin();
        int max_value = *il.begin();
        for(auto it = il.begin(); it != il.end(); it++){
            if(*it < min_value)
                min_value = *it;
            else if(*it > max_value)
                max_value = *it;
        }

        size = 0;
        max_size = max_value - min_value + 1;
        bytes_amount = ((max_size - 1) >> 5) + 1;
        values = new unsigned int[max_size];
        for(int i=0; i<max_size; i++)
            values[i] = 0;

        for(auto it = il.begin(); it != il.end(); it++){
            push(*it);
        }
    }
    else
        throw std::invalid_argument("Size of initializer list is 0");
}
Set::Set(const Set& other){
    min_value = other.min_value;
    size = other.size;
    max_size = other.max_size;
    bytes_amount = other.bytes_amount;
    values = new unsigned int[bytes_amount];
    for(int i=0; i<bytes_amount; i++)
        values[i] = other.values[i];
}
Set& Set::operator=(const Set& other){
    if(this != &other){
        delete[] values;

        min_value = other.min_value;
        size = other.size;
        max_size = other.max_size;
        bytes_amount = other.bytes_amount;
        values = new unsigned int[bytes_amount];
        for(int i=0; i<bytes_amount; i++)
            values[i] = other.values[i];
    }
    return *this;
}
Set::~Set(){
    delete[] values;
}


int Set::get_min(){
    return min_value;
}
int Set::get_max(){
    return min_value + max_size - 1;
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
    for(int i=0; i < bytes_amount; i++)
        values[i] = 0;
    size = 0;
}


void Set::push(int value){
    if(value >= min_value && value <= min_value + max_size - 1){
        std::size_t index = value - min_value;
        std::size_t which_byte = index / 32;
        index %= 32;
        values[which_byte] |= (1 << index);
        size++;
    }
}

void Set::erase(int value){
    if(value >= min_value && value <= min_value + max_size - 1){
        std::size_t index = value - min_value;
        std::size_t which_byte = index / 32;
        index %= 32;
        unsigned int temp = 1 << index;
        //if(values[which_byte] & temp)
        //    values[which_byte] -= temp;
        values[which_byte] &= ~(1 << index);
        size--;
    }
}
bool Set::contains(int value) const{
    if(value >= min_value && value <= min_value + max_size - 1){
        std::size_t index = value - min_value;
        std::size_t which_byte = index / 32;
        index %= 32;
        return (values[which_byte] & (1 << index));
    }
    return false;
}



void Set::sets_union(const Set& other){
    int new_min = std::min(min_value, other.min_value);
    int new_max = std::max(min_value + max_size - 1, other.min_value + other.max_size - 1);
    Set temp(new_min, new_max);

    int value = min_value;
    for(int i=0; i < bytes_amount; i++){
        for(unsigned int k = 1; k != 0; k <<= 1, value++) // k != 0   - there must occur integer overflow, because (1<<31) must be checked either
            if(values[i] & k)
                temp.push(value);
    }

    value = other.min_value;
    for(int i=0; i < other.bytes_amount; i++){
        for(unsigned int k = 1; k != 0; k <<= 1, value++)
            if(other.values[i] & k)
                temp.push(value);
    }

    *this = temp;
}
void Set::intersection(const Set& other){
    int value = min_value;
    for(int i=0; i < bytes_amount; i++){
        for(unsigned int k = 1; k != 0; k <<= 1, value++)
            if((values[i] & k) && !other.contains(value))
                erase(value);
    }
}
void Set::difference(const Set& other){
    int value = other.min_value;
    for(int i=0; i<other.bytes_amount; i++){
        for(unsigned int k = 1; k != 0; k <<= 1, value++)
            if((other.values[i] & k) && contains(value))
                erase(value);
    }
}
void Set::complement(){
    for(int i=0; i < bytes_amount; i++)
        values[i] = ~values[i];
    size = max_size - size;
}

bool Set::is_subset(const Set& subset){
    int value = subset.min_value;
    for(int i=0; i<subset.bytes_amount; i++){
        for(unsigned int k = 1; k != 0; k <<= 1, value++)
            if((subset.values[i] & k) && !contains(value))
                return false;
    }
    return true;
}





std::ostream& operator<< (std::ostream& os, const Set& set)
{
    int i=set.bytes_amount-1;

    int number = set.max_size % 32;
    if(number != 0){
        unsigned int k = 1 << (number-1);
        for(;k > 0; k >>= 1)
            os << ((set.values[i] & k) != 0);
        i--;
    }

    for(; i >= 0; i--)
        os << std::bitset<32>(set.values[i]);

    return os;
}

