#pragma once


template<class T>
class DoublyLinkedList
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
    DoublyLinkedList();
    DoublyLinkedList(std::initializer_list<T> il);
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();

    //
    class iterator :public std::iterator<std::bidirectional_iterator_tag, T>
    {
        friend DoublyLinkedList;
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

    class reverse_iterator :public iterator
    {
    public:
        reverse_iterator() :iterator(nullptr) {}
        reverse_iterator(Node* ptr) :iterator(ptr) {}
        reverse_iterator(const iterator& other) :iterator(other.p) {}
        reverse_iterator& operator=(const iterator& other) {iterator::p = other.p; return *this;}

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

    void partition(iterator start, iterator stop);
    void quick_sort();

    iterator find(T value);
    iterator mtf_find(T value);
    iterator transpose_find(T value);

};


template<class T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> il)
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
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
{
    head = tail = nullptr;
    size = 0;

    Node* it_other = other.head;
    while(it_other != nullptr)
    {
        Node* node = new Node;
        node->next = nullptr;
        node->prev = tail;
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
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
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
DoublyLinkedList<T>::~DoublyLinkedList()
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
std::size_t DoublyLinkedList<T>::get_size()
{
    return size;
}
template<class T>
bool DoublyLinkedList<T>::empty()
{
    return (head == nullptr);
}



template<class T>
void DoublyLinkedList<T>::push_front(T data)
{
    Node* node = new Node;
    node->next = head;
    node->prev = nullptr;
    node->data = data;
    if(head != nullptr)
        head->prev = node;
    else
        tail = node;
    head = node;
    ++size;
}
template<class T>
void DoublyLinkedList<T>::push_back(T data)
{
    Node* node = new Node;
    node->next = nullptr;
    node->prev = tail;
    node->data = data;
    if(tail != nullptr)
        tail->next = node;
    else
        head = node;
    tail = node;
    ++size;
}

template<class T>
void DoublyLinkedList<T>::pop_front()
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
void DoublyLinkedList<T>::pop_back()
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
void DoublyLinkedList<T>::insert(std::size_t pos, T data)
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
            node->data = data;

            it->next->prev = node;
            it->next = node;
            ++size;
        }
    }
}
template<class T>
void DoublyLinkedList<T>::erase(std::size_t pos)
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
void DoublyLinkedList<T>::clear()
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
void DoublyLinkedList<T>::quick_sort()
{
    if(head->next != nullptr)
    {
        push_front(0);
        push_back(0);
        partition(head, tail);
        pop_front();
        pop_back();
    }
}

template<class T>
void DoublyLinkedList<T>::partition(typename DoublyLinkedList<T>::iterator start, typename DoublyLinkedList<T>::iterator stop)
{
    if(start != nullptr && start != stop)
    {
        Node* startp = start.p;
        Node* stopp = stop.p;

        Node* pivot = startp->next;
        Node* it = pivot->next;

        if(it != stopp)
        {
            do{
                Node* itn = it->next;
                if(it->data < pivot->data)
                {
                    it->prev->next = it->next;
                    it->next->prev = it->prev;

                    it->next = pivot;
                    it->prev = pivot->prev;
                    pivot->prev = it;
                    it->prev->next = it;
                }
                it = itn;
            }while(it != stopp);

            if(pivot != startp->next)
                partition(startp, pivot);
            if(pivot != stopp->prev)
                partition(pivot, stopp);
        }
    }
}



template<class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::find(T value)
{
    Node* it = head;
    while(it != nullptr && it->data != value)
        it = it->next;
    return iterator(it);
}

template<class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::mtf_find(T value)
{
    // move-to-front method

    if(head)
    {
        Node* it = head;
        while(it != nullptr && it->data != value)
            it = it->next;

        if(it && it != head)
        {
            if(it->next)
                it->next->prev = it->prev;
            else
                tail = it->prev;

            if(it->prev)
            {
                it->prev->next = it->next;

                it->prev = nullptr;
                it->next = head;
                head = it;
                if(it->next)
                    it->next->prev = it;
            }
        }

        return it;
    }
    return nullptr;
}



template<class T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::transpose_find(T value)
{
    // transpose method

    if(head)
    {
        Node* it = head;
        while(it != nullptr && it->data != value)
            it = it->next;

        if(it && it != head)
        {
            Node* it2 = it->prev;

            if(it2->prev)
                it2->prev->next = it;
            else
                head = it;

            if(it->next)
                it->next->prev = it2;
            else
                tail = it2;

            it2->next = it->next;
            it->next = it2;
            it->prev = it2->prev;
            it2->prev = it;
        }

        return it;
    }
    return nullptr;
}
