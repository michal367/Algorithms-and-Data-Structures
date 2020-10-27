#pragma once

template<class T>
class PriorityQueue
{
    // max priority queue

    struct Node
    {
        Node* next;
        T data;
        std::size_t prio;
    };

    Node* head;
    std::size_t size;

public:

    PriorityQueue();
    PriorityQueue(const PriorityQueue<T>& other);
    PriorityQueue<T>& operator=(const PriorityQueue<T>& other);
    ~PriorityQueue();

    std::size_t get_size();
    bool empty();

    void push(T data, std::size_t priority);
    void pop();

    T front();
    std::size_t front_priority();

    void erase(std::size_t pos);
    void erase_priority(std::size_t priority);
    void clear();


    std::size_t count(T data);

};


template<class T>
PriorityQueue<T>::PriorityQueue() : head(nullptr), size(0) {}

template<class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& other)
{
    head = nullptr;
    size = 0;
    if(other.head != nullptr)
    {
        Node* node = new Node;
        node->next = nullptr;
        node->data = other.head->data;
        node->prio = other.head->prio;
        head = node;
        Node* it_p = head;

        Node* it = other.head->next;
        while(it != nullptr)
        {
            Node* node = new Node;
            node->next = nullptr;
            node->data = it->data;
            node->prio = it->prio;
            it_p->next = node;
            it_p = node;
            it = it->next;
        }
    }
    size = other.size;
}
template<class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& other)
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
            node->prio = other.head->prio;
            head = node;
            Node* it_p = head;

            Node* it = other.head->next;
            while(it != nullptr)
            {
                Node* node = new Node;
                node->next = nullptr;
                node->data = it->data;
                node->prio = it->prio;
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
PriorityQueue<T>::~PriorityQueue()
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
std::size_t PriorityQueue<T>::get_size()
{
    return size;
}
template<class T>
bool PriorityQueue<T>::empty()
{
    return (head == nullptr);
}
template<class T>
T PriorityQueue<T>::front()
{
    if(head != nullptr)
        return head->data;
}
template<class T>
std::size_t PriorityQueue<T>::front_priority()
{
    if(head != nullptr)
        return head->prio;
}


template<class T>
void PriorityQueue<T>::push(T data, std::size_t priority)
{
    Node* node = new Node;
    node->data = data;
    node->prio = priority;

    if(head != nullptr)
    {
        if(priority > head->prio)
        {
            node->next = head;
            head = node;
        }
        else
        {
            Node* it = head;
            while(it->next != nullptr && priority <= it->next->prio)
                it = it->next;
            node->next = it->next;
            it->next = node;
        }
    }
    else
    {
        head = node;
        node->next = nullptr;
    }
    ++size;
}
template<class T>
void PriorityQueue<T>::pop()
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
void PriorityQueue<T>::erase(std::size_t pos)
{
    if(pos < size)
    {
        if(pos == 0)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            Node* it = head;
            for(std::size_t i=0; i<pos-1; ++i)
                it = it->next;
            Node* next = it->next->next;
            delete it->next;
            it->next = next;
        }
        --size;
    }
}
template<class T>
void PriorityQueue<T>::erase_priority(std::size_t priority)
{
    if(head != nullptr)
    {
        if(head->prio == priority)
        {
            Node* it = head;
            while(it != nullptr && it->prio == priority)
            {
                Node* temp = it->next;
                delete it;
                --size;
                it = temp;
            }
            head = it;
        }
        else
        {
            Node* it = head;
            while(it->next != nullptr && it->next->prio != priority)
                it = it->next;
            if(it->next != nullptr && it->next->prio == priority)
            {
                Node* temp = it;
                it = it->next;
                while(it != nullptr && it->prio == priority)
                {
                    Node* temp2 = it->next;
                    delete it;
                    --size;
                    it = temp2;
                }
                temp->next = it;
            }
        }
    }
}


template<class T>
void PriorityQueue<T>::clear()
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

