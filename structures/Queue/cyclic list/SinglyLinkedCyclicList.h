#pragma once


template<class T>
class SinglyLinkedCyclicList
{
    struct Node
    {
        Node* next;
        T data;
    };

    Node* tail;
    std::size_t size;

public:

    SinglyLinkedCyclicList();
    SinglyLinkedCyclicList(std::initializer_list<T> il);
    SinglyLinkedCyclicList(const SinglyLinkedCyclicList<T>& other);
    SinglyLinkedCyclicList<T>& operator=(const SinglyLinkedCyclicList<T>& other);
    ~SinglyLinkedCyclicList();


    //

    class iterator :public std::iterator<std::forward_iterator_tag, T>
    {
    protected:
        Node* p;
    public:
        iterator() :p(nullptr) {}
        iterator(Node* ptr) :p(ptr) {}
        iterator(const iterator& other) :p(other.p) {}
        iterator& operator=(const iterator& other) {p = other.p; return *this;}
        T& operator*() {return p->data;}
        T* operator->() {return &(p->data);}

        iterator operator++() {p = p->next; return *this;}
        iterator operator++(int) {iterator clone(*this); p = p->next; return clone;}

        bool operator==(const iterator& other) {return (p == other.p);}
        bool operator!=(const iterator& other) {return (p != other.p);}
    };

    iterator begin() {return iterator(tail);};
    iterator end() {return iterator(nullptr);};


    //

    std::size_t get_size();
    bool empty();
    T front();

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();

    void insert(std::size_t pos, T data);
    void erase(std::size_t pos);
    void clear();


    iterator find(T data);

};


template<class T>
SinglyLinkedCyclicList<T>::SinglyLinkedCyclicList() : tail(nullptr), size(0) {}


template<class T>
SinglyLinkedCyclicList<T>::SinglyLinkedCyclicList(std::initializer_list<T> il)
{
    tail = nullptr;
    size = 0;
    for(typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it)
        push_back(*it);
}

template<class T>
SinglyLinkedCyclicList<T>::SinglyLinkedCyclicList(const SinglyLinkedCyclicList<T>& other)
{
    if(other.tail != nullptr)
    {
        Node* node = new Node;
        node->next = node;
        node->data = other.tail->data;
        tail = node;

        Node* it_p = tail;
        Node* it = other.tail->next;
        while(it != other.tail)
        {
            Node* node = new Node;
            node->next = tail;
            node->data = it->data;
            it_p->next = node;
            it_p = node;
            it = it->next;
        }
    }
    size = other.size;
}
template<class T>
SinglyLinkedCyclicList<T>& SinglyLinkedCyclicList<T>::operator=(const SinglyLinkedCyclicList<T>& other)
{
    if(tail != nullptr)
        clear();

    if(other.tail != nullptr)
    {
        Node* node = new Node;
        node->next = node;
        node->data = other.tail->data;
        tail = node;

        Node* it_p = tail;
        Node* it = other.tail->next;
        while(it != other.tail)
        {
            Node* node = new Node;
            node->next = tail;
            node->data = it->data;
            it_p->next = node;
            it_p = node;
            it = it->next;
        }
    }
    size = other.size;

    return *this;
}

template<class T>
SinglyLinkedCyclicList<T>::~SinglyLinkedCyclicList()
{
    if(tail != nullptr)
    {
        Node* temp = tail;
        Node* it = tail->next;
        Node* it2 = it->next;
        delete tail;
        while(it != temp)
        {
            delete it;
            it = it2;
            if(it2 != temp)
                it2 = it->next;
        }

        tail = nullptr;
        size = 0;
    }
}





template<class T>
std::size_t SinglyLinkedCyclicList<T>::get_size()
{
    return size;
}
template<class T>
bool SinglyLinkedCyclicList<T>::empty()
{
    return (tail == nullptr);
}
template<class T>
T SinglyLinkedCyclicList<T>::front()
{
    return tail->next->data;
}



template<class T>
void SinglyLinkedCyclicList<T>::push_front(T data)
{
    Node* node = new Node;
    node->data = data;

    if(tail != nullptr)
    {
        node->next = tail->next;
        tail->next = node;
    }
    else
    {
        tail = node;
        tail->next = tail;
    }
    ++size;
}
template<class T>
void SinglyLinkedCyclicList<T>::push_back(T data)
{
    Node* node = new Node;
    node->data = data;

    if(tail != nullptr)
    {
        node->next = tail->next;
        tail->next = node;
        tail = node;
    }
    else
    {
        tail = node;
        tail->next = tail;
    }
    ++size;
}


template<class T>
void SinglyLinkedCyclicList<T>::pop_front()
{
    if(tail != nullptr)
    {
        if(tail->next != tail)
        {
            Node* temp = tail->next->next;
            delete tail->next;
            tail->next = temp;
        }
        else
        {
            delete tail;
            tail = nullptr;
        }
        --size;
    }
}
template<class T>
void SinglyLinkedCyclicList<T>::pop_back()
{
    if(tail != nullptr)
    {
        if(tail->next != tail)
        {
            Node* it = tail->next;
            while(it->next != tail)
                it = it->next;
            it->next = tail->next;
            delete tail;
            tail = it;
        }
        else
        {
            delete tail;
            tail = nullptr;
        }
        --size;
    }
}


template<class T>
void SinglyLinkedCyclicList<T>::insert(std::size_t pos, T data)
{
    if(pos <= size)
    {
        if(pos == 0)
            push_front(data);
        else if(pos == size)
            push_back(data);
        else
        {
            Node* it = tail;
            for(std::size_t i=0; i<pos-1; ++i)
                it = it->next;
            Node* node = new Node;
            node->next = it->next;
            node->data = data;
            it->next = node;
            ++size;
        }
    }
}
template<class T>
void SinglyLinkedCyclicList<T>::erase(std::size_t pos)
{
    if(pos < size)
    {
        if(pos == 0)
            pop_front();
        else if(pos == size-1)
            pop_back();
        else
        {
            Node* it = tail;
            for(std::size_t i=0; i<pos-1; ++i)
                it = it->next;
            Node* next = it->next->next;
            delete it->next;
            it->next = next;
            --size;
        }
    }
}
template<class T>
void SinglyLinkedCyclicList<T>::clear()
{
    if(tail != nullptr)
    {
        Node* temp = tail;
        Node* it = tail->next;
        Node* it2 = it->next;
        delete tail;
        while(it != temp)
        {
            delete it;
            it = it2;
            if(it2 != temp)
                it2 = it->next;
        }

        tail = nullptr;
        size = 0;
    }
}




template<class T>
typename SinglyLinkedCyclicList<T>::iterator SinglyLinkedCyclicList<T>::find(T data)
{
    Node* it = tail;
    while(it && it->data != data)
    {
        it = it->next;
        if(it->data != data && it->next == tail)
            it = nullptr;
    }
    return iterator(it);
}
