#pragma once

#include <vector>

template<class T>
class DisjointSets
{
    struct Node
    {
        T value;
        std::size_t rank;
        Node* parent;
    };
    std::vector<Node*> elements;

public:
    DisjointSets();
    DisjointSets(const DisjointSets<T>& other);
    DisjointSets<T>& operator=(const DisjointSets<T>& other);
    ~DisjointSets();

    class iterator :public std::iterator<std::bidirectional_iterator_tag, T>
    {
        Node* ptr;
        friend DisjointSets;
    public:
        iterator() : ptr(NULL) {}
        iterator(Node* p) : ptr(p) {}
        iterator(const iterator& other) : ptr(other.ptr) {}
        iterator& operator=(const iterator& other) {ptr = other.ptr; return *this;}

        T& operator*() {return ptr->value;}
        T* operator->() {return &(ptr->value);}

        bool operator==(iterator b) {return ptr == b.ptr;}
        bool operator!=(iterator b) {return ptr != b.ptr;}

        iterator parent() {return ptr->parent;}
        std::size_t rank() {return ptr->rank;}
    };

    iterator begin() {
        if(elements.empty())
            return nullptr;
        else
            return iterator(elements.at(0));
    }
    iterator end() {return nullptr;}

    void makeSet(T element);
    void addElement(T element, T dest);
    bool include(T element);
    typename DisjointSets<T>::iterator find(T element);
    typename DisjointSets<T>::iterator findSet(T element);
    void unionSets(T element1, T element2);

    typename DisjointSets<T>::iterator findSet(typename DisjointSets<T>::iterator element);
    void unionSets(typename DisjointSets<T>::iterator element1, typename DisjointSets<T>::iterator element2);

    std::size_t size();
    DisjointSets<T>::iterator getElement(std::size_t index);
};

template<class T>
DisjointSets<T>::DisjointSets() {}
template<class T>
DisjointSets<T>::DisjointSets(const DisjointSets<T>& other)
{
    for(auto it = other.elements.begin(); it != other.elements.end(); ++it)
    {
        Node* new_node = new Node;
        new_node->value = (*it)->value;
        new_node->rank = (*it)->rank;
        new_node->parent = (*it)->parent;
        elements.push_back(new_node);
    }
}
template<class T>
DisjointSets<T>& DisjointSets<T>::operator=(const DisjointSets<T>& other)
{
    if(!elements.empty())
    {
        for(auto it = elements.begin(); it != elements.end(); ++it)
            delete *it;
        elements.clear();
    }
    if(this != &other)
    {
        for(auto it = other.elements.begin(); it != other.elements.end(); ++it)
        {
            Node* new_node = new Node;
            new_node->value = (*it)->value;
            new_node->rank = (*it)->rank;
            new_node->parent = (*it)->parent;
            elements.push_back(new_node);
        }
    }
    return *this;
}
template<class T>
DisjointSets<T>::~DisjointSets()
{
    for(auto it = elements.begin(); it != elements.end(); ++it)
        delete *it;
    elements.clear();
}

template<class T>
void DisjointSets<T>::makeSet(T element)
{
    if(!include(element))
    {
        Node* new_node = new Node;
        new_node->value = element;
        new_node->rank = 0;
        new_node->parent = new_node;
        elements.push_back(new_node);
    }
}
template<class T>
void DisjointSets<T>::addElement(T element, T dest)
{
    for(auto it = elements.begin(); it != elements.end(); ++it)
        if((*it)->value == dest)
        {
            Node* new_node = new Node;
            new_node->value = element;
            new_node->rank = 0;
            new_node->parent = *it;
            elements.push_back(new_node);
            return;
        }
}
template<class T>
bool DisjointSets<T>::include(T element)
{
    for(auto it = elements.begin(); it != elements.end(); ++it)
        if((*it)->value == element)
            return true;
    return false;
}
template<class T>
typename DisjointSets<T>::iterator DisjointSets<T>::find(T element)
{
    for(auto it = elements.begin(); it != elements.end(); ++it)
        if((*it)->value == element)
            return iterator(*it);
    return nullptr;
}
template<class T>
typename DisjointSets<T>::iterator DisjointSets<T>::findSet(T element)
{
    for(auto it = elements.begin(); it != elements.end(); ++it)
        if((*it)->value == element)
        {
            Node* temp = *it;
            while(temp != temp->parent)
                temp = temp->parent;
            Node* temp2 = *it;
            while(temp2 != temp2->parent)
            {
                Node* temp3 = temp2;
                temp2 = temp2->parent;
                temp3->parent = temp;
            }
            return iterator(temp);
        }
    return nullptr;
}
template<class T>
void DisjointSets<T>::unionSets(T element1, T element2)
{
    if(element1 != element2)
    {
        Node* x=nullptr, *y=nullptr;
        for(auto it = elements.begin(); it != elements.end(); ++it)
            if((*it)->value == element1)
            {
                x = *it;
                while(x != x->parent)
                    x = x->parent;
                break;
            }
        for(auto it = elements.begin(); it != elements.end(); ++it)
            if((*it)->value == element2)
            {
                y = *it;
                while(y != y->parent)
                    y = y->parent;
                break;
            }

        if(x != nullptr && y != nullptr)
        {
            if(x->rank > y->rank)
                y->parent = x;
            else
            {
                x->parent = y;
                if(x->rank == y->rank)
                    y->rank++;
            }
        }
    }
}

template<class T>
typename DisjointSets<T>::iterator DisjointSets<T>::findSet(typename DisjointSets<T>::iterator element)
{
    Node* temp = element.ptr;
    while(element != element.parent())
        element = element.parent();
    Node* temp2 = temp;
    while(temp2 != temp2->parent)
    {
        Node* temp3 = temp2;
        temp2 = temp2->parent;
        temp3->parent = element.ptr;
    }
    return element;
}
template<class T>
void DisjointSets<T>::unionSets(typename DisjointSets<T>::iterator element1, typename DisjointSets<T>::iterator element2)
{
    while(element1 != element1.parent())
        element1 = element1.parent();
    while(element2 != element2.parent())
        element2 = element2.parent();

    if(element1.ptr->rank > element2.ptr->rank)
        element2.ptr->parent = element1.ptr;
    else
    {
        element1.ptr->parent = element2.ptr;
        if(element1.ptr->rank == element2.ptr->rank)
            element2.ptr->rank++;
    }
}

template<class T>
std::size_t DisjointSets<T>::size()
{
    return elements.size();
}
template<class T>
typename DisjointSets<T>::iterator DisjointSets<T>::getElement(std::size_t index)
{
    return iterator(elements.at(index));
}

