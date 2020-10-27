#pragma once


template<class T>
class DisjointSetsList
{
    struct Node
    {
        Node* next;
        Node* prev;
        T data;
    };

    Node* head;
    Node* tail;
    std::size_t size;

public:
    DisjointSetsList();
    DisjointSetsList(std::initializer_list<T> il);
    DisjointSetsList(const DisjointSetsList<T>& other);
    DisjointSetsList<T>& operator=(const DisjointSetsList<T>& other);
    ~DisjointSetsList();

    //
    class iterator :public std::iterator<std::bidirectional_iterator_tag, T>
    {
        friend DisjointSetsList;
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
        iterator operator--() {p = p->prev; return *this;}
        iterator operator--(int) {iterator clone(*this); p = p->prev; return clone;}

        bool operator==(const iterator& other) {return (p == other.p);}
        bool operator!=(const iterator& other) {return (p != other.p);}
    };

    iterator begin() {return iterator(head);}
    iterator end() {return iterator(nullptr);}

    //

    std::size_t get_size();
    bool empty();

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();

    void insert(std::size_t pos, T data);
    void erase(std::size_t pos);
    void splice_list(DisjointSetsList& second);
    void clear();

};


template<class T>
DisjointSetsList<T>::DisjointSetsList() : head(nullptr), tail(nullptr), size(0) {}

template<class T>
DisjointSetsList<T>::DisjointSetsList(std::initializer_list<T> il)
{
    head = tail = nullptr;
    size = 0;
    if(il.size() > 0)
    {
        for(typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it)
        {
            Node* node = new Node;
            node->next = nullptr;
            node->prev = head;
            node->data = *it;

            if(head != nullptr)
            {
                tail->next = node;
                tail = node;
            }
            else
            {
                head = tail = node;
                node->prev = node;
            }
            ++size;
        }
    }
}

template<class T>
DisjointSetsList<T>::DisjointSetsList(const DisjointSetsList<T>& other)
{
    head = tail = nullptr;
    size = 0;

    Node* it_other = other.head;
    while(it_other != nullptr)
    {
        Node* node = new Node;
        node->next = nullptr;
        node->prev = head;
        node->data = it_other->data;

        if(head != nullptr)
        {
            tail->next = node;
            tail = node;
        }
        else
        {
            head = tail = node;
            node->prev = node;
        }
        it_other = it_other->next;
    }
    size = other.size;
}

template<class T>
DisjointSetsList<T>& DisjointSetsList<T>::operator=(const DisjointSetsList<T>& other)
{
    if(this != &other)
    {
        if(!empty())
            clear();

        Node* it_other = other.head;
        while(it_other != nullptr)
        {
            Node* node = new Node;
            node->next = nullptr;
            node->prev = head;
            node->data = it_other->data;

            if(head != nullptr)
            {
                tail->next = node;
                tail = node;
            }
            else
            {
                head = tail = node;
                node->prev = node;
            }
            it_other = it_other->next;
        }
        size = other.size;
    }
    return *this;
}

template<class T>
DisjointSetsList<T>::~DisjointSetsList()
{
    if(head != nullptr)
    {
        Node* it = head;
        Node* it2 = it->next;
        while(it != nullptr)
        {
            delete it;
            it = it2;
            if(it2 != nullptr)
                it2 = it->next;
        }

        head = tail = nullptr;
        size = 0;
    }
}





template<class T>
std::size_t DisjointSetsList<T>::get_size()
{
    return size;
}
template<class T>
bool DisjointSetsList<T>::empty()
{
    return (head == nullptr);
}



template<class T>
void DisjointSetsList<T>::push_front(T data)
{
    Node* node = new Node;
    node->next = head;
    node->prev = node;
    node->data = data;

    Node* it = head;
    while(it != nullptr)
    {
        it->prev = node;
        it = it->next;
    }
    if(head == nullptr)
        tail = node;
    head = node;
    ++size;
}
template<class T>
void DisjointSetsList<T>::push_back(T data)
{
    Node* node = new Node;
    node->next = nullptr;
    node->prev = head;
    node->data = data;
    if(tail != nullptr)
        tail->next = node;
    else
        head = node;
    tail = node;
    ++size;
}

template<class T>
void DisjointSetsList<T>::pop_front()
{
    if(head != nullptr)
    {
        Node* temp = head->next;
        delete head;
        head = temp;
        Node* it = head;
        while(it != nullptr)
        {
            it->prev = head;
            it = it->next;
        }
        --size;
    }
}
template<class T>
void DisjointSetsList<T>::pop_back()
{
    if(tail != nullptr)
    {
        Node* it = head;
        while(it->next->next != nullptr)
            it = it->next;
        delete tail;
        tail = it;
        if(tail != nullptr)
            tail->next = nullptr;
        --size;
    }
}

template<class T>
void DisjointSetsList<T>::insert(std::size_t pos, T data)
{
    if(pos <= size)
    {
        if(pos == 0)
            push_front(data);
        else if(pos == size)
            push_back(data);
        else
        {
            Node* it = head;
            for(std::size_t i=0; i<pos-1; ++i)
                it = it->next;

            Node* node = new Node;
            node->next = it->next;
            node->prev = head;
            node->data = data;

            it->next = node;
            ++size;
        }
    }
}
template<class T>
void DisjointSetsList<T>::erase(std::size_t pos)
{
    if(pos < size)
    {
        if(pos == 0)
            pop_front();
        else if(pos == size)
            pop_back();
        else
        {
            Node* it = head;
            for(std::size_t i = 0; i<pos-1; ++i)
                it = it->next;

            Node* temp = it->next;
            it->next = it->next->next;
            delete temp;

            --size;
        }
    }
}


template<class T>
void DisjointSetsList<T>::splice_list(DisjointSetsList& second)
{
    tail->next = second.head;
    Node* it = second.head;
    while(it != nullptr)
    {
        it->prev = head;
        it = it->next;
    }
    tail = second.tail;
    size += second.size;

    second.head = second.tail = nullptr;
    second.size = 0;
}




template<class T>
void DisjointSetsList<T>::clear()
{
    if(head != nullptr)
    {
        Node* it = head;
        while(it->next != nullptr)
        {
            it = it->next;
            delete it->prev;
        }
        delete tail;

        head = tail = nullptr;
        size = 0;
    }
}

