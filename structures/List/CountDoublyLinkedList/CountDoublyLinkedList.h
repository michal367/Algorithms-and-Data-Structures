#pragma once


template<class T>
class CountDoublyLinkedList
{
    // self organizing list - count method

    struct Node
    {
        Node* next;
        Node* prev;
        std::size_t count;
        T data;
    };

    Node* head;
    Node* tail;
    std::size_t size;

public:
    CountDoublyLinkedList();
    CountDoublyLinkedList(std::initializer_list<T> il);
    CountDoublyLinkedList(const CountDoublyLinkedList<T>& other);
    CountDoublyLinkedList<T>& operator=(const CountDoublyLinkedList<T>& other);
    ~CountDoublyLinkedList();

    //
    class iterator :public std::iterator<std::bidirectional_iterator_tag, T>
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

        std::size_t count() {return iterator::p->count;}

        iterator operator++() {p = p->next; return *this;}
        iterator operator++(int) {iterator clone(*this); p = p->next; return clone;}
        iterator operator--() {p = p->prev; return *this;}
        iterator operator--(int) {iterator clone(*this); p = p->prev; return clone;}

        bool operator==(const iterator& other) {return (p == other.p);}
        bool operator!=(const iterator& other) {return (p != other.p);}
    };

    class reverse_iterator :public iterator
    {
    public:
        reverse_iterator() :iterator(nullptr) {}
        reverse_iterator(Node* ptr) :iterator(ptr) {}
        reverse_iterator(const iterator& other) :iterator(other.p) {}
        reverse_iterator& operator=(const iterator& other) {iterator::p = other.p; return *this;}

        std::size_t count() {return iterator::p->count;}

        reverse_iterator operator++() {iterator::p = iterator::p->prev; return *this;}
        reverse_iterator operator++(int) {reverse_iterator clone(*this); iterator::p = iterator::p->prev; return clone;}
        reverse_iterator operator--() {iterator::p = iterator::p->next; return *this;}
        reverse_iterator operator--(int) {reverse_iterator clone(*this); iterator::p = iterator::p->next; return clone;}
    };

    iterator begin() {return iterator(head);}
    iterator end() {return iterator(nullptr);}
    reverse_iterator rbegin() {return reverse_iterator(tail);}
    reverse_iterator rend() {return reverse_iterator(nullptr);}

    //

    std::size_t get_size();
    bool empty();

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();

    void insert(std::size_t pos, T data);
    void erase(std::size_t pos);
    void clear();

    iterator count_find(T value);

};


template<class T>
CountDoublyLinkedList<T>::CountDoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<class T>
CountDoublyLinkedList<T>::CountDoublyLinkedList(std::initializer_list<T> il)
{
    head = tail = nullptr;
    size = 0;
    if(il.size() > 0)
    {
        for(typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it)
        {
            Node* node = new Node;
            node->next = nullptr;
            node->prev = tail;
            node->count = 0;
            node->data = *it;

            if(head != nullptr)
            {
                tail->next = node;
                tail = node;
            }
            else
            {
                head = tail = node;
            }
            ++size;
        }
    }
}

template<class T>
CountDoublyLinkedList<T>::CountDoublyLinkedList(const CountDoublyLinkedList<T>& other)
{
    head = tail = nullptr;
    size = 0;

    Node* it_other = other.head;
    while(it_other != nullptr)
    {
        Node* node = new Node;
        node->next = nullptr;
        node->prev = tail;
        node->count = 0;
        node->data = it_other->data;

        if(head != nullptr)
        {
            tail->next = node;
            tail = node;
        }
        else
        {
            head = tail = node;
        }
        it_other = it_other->next;
    }
    size = other.size;
}

template<class T>
CountDoublyLinkedList<T>& CountDoublyLinkedList<T>::operator=(const CountDoublyLinkedList<T>& other)
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
            node->prev = tail;
            node->count = 0;
            node->data = it_other->data;

            if(head != nullptr)
            {
                tail->next = node;
                tail = node;
            }
            else
            {
                head = tail = node;
            }
            it_other = it_other->next;
        }
        size = other.size;
    }
    return *this;
}

template<class T>
CountDoublyLinkedList<T>::~CountDoublyLinkedList()
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





template<class T>
std::size_t CountDoublyLinkedList<T>::get_size()
{
    return size;
}
template<class T>
bool CountDoublyLinkedList<T>::empty()
{
    return (head == nullptr);
}



template<class T>
void CountDoublyLinkedList<T>::push_front(T data)
{
    Node* node = new Node;
    node->next = head;
    node->prev = nullptr;
    node->count = 0;
    node->data = data;
    if(head != nullptr)
        head->prev = node;
    else
        tail = node;
    head = node;
    ++size;
}
template<class T>
void CountDoublyLinkedList<T>::push_back(T data)
{
    Node* node = new Node;
    node->next = nullptr;
    node->prev = tail;
    node->count = 0;
    node->data = data;
    if(tail != nullptr)
        tail->next = node;
    else
        head = node;
    tail = node;
    ++size;
}

template<class T>
void CountDoublyLinkedList<T>::pop_front()
{
    if(head != nullptr)
    {
        Node* temp = head->next;
        delete head;
        head = temp;
        if(head != nullptr)
            head->prev = nullptr;
        --size;
    }
}
template<class T>
void CountDoublyLinkedList<T>::pop_back()
{
    if(tail != nullptr)
    {
        Node* temp = tail->prev;
        delete tail;
        tail = temp;
        if(tail != nullptr)
            tail->next = nullptr;
        --size;
    }
}

template<class T>
void CountDoublyLinkedList<T>::insert(std::size_t pos, T data)
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
            node->prev = it;
            node->count = 0;
            node->data = data;

            it->next->prev = node;
            it->next = node;
            ++size;
        }
    }
}
template<class T>
void CountDoublyLinkedList<T>::erase(std::size_t pos)
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
            for(std::size_t i = 0; i<pos; ++i)
                it = it->next;

            it->prev->next = it->next;
            it->next->prev = it->prev;
            delete it;

            --size;
        }
    }
}


template<class T>
void CountDoublyLinkedList<T>::clear()
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



template<class T>
typename CountDoublyLinkedList<T>::iterator CountDoublyLinkedList<T>::count_find(T value)
{
    if(head)
    {
        Node* it = head;
        while(it != nullptr && it->data != value)
            it = it->next;

        if(it)
        {
            ++it->count;

            Node* it2 = it;
            while(it2->prev != nullptr && it2->prev->count <= it->count)
                it2 = it2->prev;

            if(it2 != it)
            {
                if(it->prev)
                    it->prev->next = it->next;
                if(it->next)
                    it->next->prev = it->prev;
                else
                    tail = it->prev;

                it->prev = it2->prev;
                it->next = it2;
                if(it->next)
                    it->next->prev = it;
                if(it->prev)
                    it->prev->next = it;
                if(it2 == head)
                    head = it;
            }
        }

        return it;
    }
}
