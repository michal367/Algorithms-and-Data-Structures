#pragma once

#include <vector>

template<class T>
class SinglyLinkedList
{
    struct Node
    {
        Node* next;
        T data;
    };

    Node* head;
    std::size_t size;

public:

    SinglyLinkedList();
    SinglyLinkedList(std::initializer_list<T> il);
    SinglyLinkedList(const SinglyLinkedList<T>& other);
    SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
    ~SinglyLinkedList();


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

    iterator begin() {return iterator(head);};
    iterator end() {return iterator(nullptr);};


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


    iterator find(T data);
    iterator sentinel_find(T data);

    iterator max();
    iterator min();

    std::size_t count(T data);

    void erase_duplicates();
    void erase_duplicates_sorted();

    void reverse();

    std::vector<SinglyLinkedList<T> > divide_into_two_parts();
    void divide_into_two_parts(SinglyLinkedList<T>& first, SinglyLinkedList<T>& second);
    void divide_into_two_parts2(SinglyLinkedList<T>& first, SinglyLinkedList<T>& second);

    void merge_two_sorted_lists(SinglyLinkedList<T>& first, SinglyLinkedList<T>& second);

    void merge_sort();
    void insert_sort();

};


template<class T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), size(0) {}


template<class T>
SinglyLinkedList<T>::SinglyLinkedList(std::initializer_list<T> il)
{
    head = nullptr;
    size = 0;
    for(typename std::initializer_list<T>::iterator it = il.begin(); it != il.end(); ++it)
        push_back(*it);
}

template<class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
{
    head = nullptr;
    size = 0;
    if(other.head != nullptr)
    {
        Node* node = new Node;
        node->next = nullptr;
        node->data = other.head->data;
        head = node;
        Node* it_p = head;

        Node* it = other.head->next;
        while(it != nullptr)
        {
            Node* node = new Node;
            node->next = nullptr;
            node->data = it->data;
            it_p->next = node;
            it_p = node;
            it = it->next;
        }
    }
    size = other.size;
}
template<class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other)
{
    if(this != &other)
    {
        if(head != nullptr)
            clear();

        if(other.head != nullptr)
        {
            Node* node = new Node;
            node->next = nullptr;
            node->data = other.head->data;
            head = node;
            Node* it_p = head;

            Node* it = other.head->next;
            while(it != nullptr)
            {
                Node* node = new Node;
                node->next = nullptr;
                node->data = it->data;
                it_p->next = node;
                it_p = node;
                it = it->next;
            }
        }
        size = other.size;

        return *this;
    }
}

template<class T>
SinglyLinkedList<T>::~SinglyLinkedList()
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

        head = nullptr;
        size = 0;
    }
}





template<class T>
std::size_t SinglyLinkedList<T>::get_size()
{
    return size;
}
template<class T>
bool SinglyLinkedList<T>::empty()
{
    return (head == nullptr);
}



template<class T>
void SinglyLinkedList<T>::push_front(T data)
{
    Node* node = new Node;
    node->next = head;
    node->data = data;
    head = node;
    ++size;
}
template<class T>
void SinglyLinkedList<T>::push_back(T data)
{
    Node* node = new Node;
    node->next = nullptr;
    node->data = data;

    if(head != nullptr)
    {
        Node* it = head;
        while(it->next != nullptr)
            it = it->next;
        it->next = node;
    }
    else
        head = node;
    ++size;
}
template<class T>
void SinglyLinkedList<T>::pop_front()
{
    if(head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        --size;
    }
}
template<class T>
void SinglyLinkedList<T>::pop_back()
{
    if(head != nullptr)
    {
        if(head->next != nullptr)
        {
            Node* it = head;
            while(it->next->next != nullptr)
                it = it->next;
            delete it->next;
            it->next = nullptr;
        }
        else
        {
            delete head;
            head = nullptr;
        }
        --size;
    }
}


template<class T>
void SinglyLinkedList<T>::insert(std::size_t pos, T data)
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
            node->data = data;
            it->next = node;
            ++size;
        }
    }
}
template<class T>
void SinglyLinkedList<T>::erase(std::size_t pos)
{
    if(pos < size)
    {
        if(pos == 0)
            pop_front();
        else if(pos == size-1)
            pop_back();
        else
        {
            Node* it = head;
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
void SinglyLinkedList<T>::clear()
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

        head = nullptr;
        size = 0;
    }
}





template<class T>
typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::find(T data)
{
    Node* it = head;
    while(it != nullptr && it->data != data)
        it = it->next;
    return iterator(it);
}
template<class T>
typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::sentinel_find(T data)
{
    push_back(data);
    Node* it = head;
    while(it->data != data)
        it = it->next;
    if(it->next == nullptr)
        it = nullptr;
    pop_back();
    return iterator(it);
}



template<class T>
typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::max()
{
    if(head != nullptr)
    {
        Node* max = head;
        Node* it = head->next;

        while(it != nullptr)
        {
            if(it->data > max->data)
                max = it;
            it = it->next;
        }
        return iterator(max);
    }
    else
        return iterator(nullptr);
}
template<class T>
typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::min()
{
    if(head != nullptr)
    {
        Node* min = head;
        Node* it = head->next;

        while(it != nullptr)
        {
            if(it->data < min->data)
                min = it;
            it = it->next;
        }
        return iterator(min);
    }
    else
        return iterator(nullptr);
}


template<class T>
std::size_t SinglyLinkedList<T>::count(T data)
{
    std::size_t counter = 0;
    Node* it = head;
    while(it != nullptr)
    {
        if(it->data == data)
            ++counter;
        it = it->next;
    }
    return counter;
}



template<class T>
void SinglyLinkedList<T>::erase_duplicates()
{
    Node* node = head;
    while(node != nullptr && node->next != nullptr)
    {
        Node* it = node;
        while(it->next != nullptr)
        {
            if(it->next->data == node->data)
            {
                Node* temp = it->next;
                it->next = temp->next;
                delete temp;
            }
            else
                it = it->next;
        }
        node = node->next;
    }
}
template<class T>
void SinglyLinkedList<T>::erase_duplicates_sorted()
{
    Node* it = head;
    while(it->next != nullptr)
    {
        if(it->next->data == it->data)
        {
            Node* temp = it->next;
            it->next = temp->next;
            delete temp;
        }
        else
            it = it->next;
    }
}

template<class T>
void SinglyLinkedList<T>::reverse()
{
    if(head != nullptr)
    {
        Node* it = head;
        while(it->next != nullptr)
        {
            Node* next = it->next->next;
            it->next->next = head;
            head = it->next;
            it->next = next;
        }
    }
}


template<class T>
std::vector<SinglyLinkedList<T> > SinglyLinkedList<T>::divide_into_two_parts()
{
    std::vector<SinglyLinkedList<T> > result(2);

    Node* it = head;
    while(it != nullptr)
    {
        result.at(0).push_back(it->data);
        if(it->next != nullptr)
        {
            result.at(1).push_back(it->next->data);
            it = it->next->next;
        }
        else
            it = nullptr;
    }

    return result;
}

template<class T>
void SinglyLinkedList<T>::divide_into_two_parts(SinglyLinkedList<T>& first, SinglyLinkedList<T>& second)
{
    first.clear();
    second.clear();
    Node* it = head;
    while(it != nullptr)
    {
        first.push_back(it->data);
        if(it->next != nullptr)
        {
            second.push_back(it->next->data);
            it = it->next->next;
        }
        else
            it = nullptr;
    }
}

template<class T>
void SinglyLinkedList<T>::divide_into_two_parts2(SinglyLinkedList<T>& first, SinglyLinkedList<T>& second)
{
    first.clear();
    second.clear();
    if(head != nullptr)
    {
        first.head = head;
        ++first.size;
        head = head->next;

        if(head != nullptr)
        {
            second.head = head;
            ++second.size;
            head = head->next;

            Node* it1 = first.head;
            Node* it2 = second.head;
            while(head)
            {
                it1->next = head;
                ++first.size;
                it1 = it1->next;

                head = head->next;
                if(head != nullptr)
                {
                    it2->next = head;
                    ++second.size;
                    it2 = it2->next;
                    head = head->next;
                }
                else
                    head = nullptr;
            }
            it1->next = it2->next = nullptr;
        }
        size = 0;
    }
}


template<class T>
void SinglyLinkedList<T>::merge_two_sorted_lists(SinglyLinkedList<T>& first, SinglyLinkedList<T>& second)
{
    clear();
    Node* merged_it = head;

    while(first.head != nullptr || second.head != nullptr)
    {
        while((first.head != nullptr && second.head == nullptr) ||
              (first.head != nullptr && second.head != nullptr && first.head->data <= second.head->data))
        {
            if(merged_it != nullptr)
            {
                merged_it->next = first.head;
                merged_it = merged_it->next;
            }
            else
            {
                head = first.head;
                merged_it = head;
            }
            first.head = first.head->next;
            --first.size;
            ++size;
        }
        while((first.head == nullptr && second.head != nullptr) ||
              (first.head != nullptr && second.head != nullptr && second.head->data < first.head->data))
        {
            if(merged_it != nullptr)
            {
                merged_it->next = second.head;
                merged_it = merged_it->next;
            }
            else
            {
                head = second.head;
                merged_it = head;
            }
            second.head = second.head->next;
            --second.size;
            ++size;
        }
    }

    merged_it->next = nullptr;
}

template<class T>
void SinglyLinkedList<T>::merge_sort()
{
    if(size > 1)
    {
        SinglyLinkedList<T> a,b;
        divide_into_two_parts2(a,b);
        a.merge_sort();
        b.merge_sort();
        merge_two_sorted_lists(a,b);
    }
}



template<class T>
void SinglyLinkedList<T>::insert_sort()
{
    SinglyLinkedList<T> result;
    result.push_back(*max());
    result.push_front(T());

    while(head)
    {
        Node* it = result.head;
        while(it->next != nullptr && head->data > it->next->data)
            it = it->next;
        Node* temp = head->next;
        head->next = it->next;
        it->next = head;

        head = temp;
    }

    result.pop_front();
    result.pop_back();
    head = result.head;
    result.head = nullptr;
}
