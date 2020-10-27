#pragma once

#include <vector>

template <class T>
class PriorityQueue
{
    // max priority queue

    struct Elem{
        T data;
        std::size_t prio;
    };
    std::vector<Elem> heap;

public:
    PriorityQueue();
    PriorityQueue(T value);
    PriorityQueue(const PriorityQueue& other);
    PriorityQueue& operator=(const PriorityQueue& other);

    void push(T value, std::size_t priority);
    T pop();

    T front();
    std::size_t front_priority();

    size_t size();
    T at(size_t index);
    bool empty();
};


template <class T>
PriorityQueue<T>::PriorityQueue() {}

template <class T>
PriorityQueue<T>::PriorityQueue(T value)
{
    heap.push_back(value);
}

template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& other)
{
    heap = other.heap;
}
template <class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue& other)
{
    if(this != &other)
        heap = other.heap;
    return *this;
}


template <class T>
void PriorityQueue<T>::push(T value, std::size_t priority)
{
    Elem el;
    el.data = value;
    el.prio = priority;
    heap.push_back(el);

    size_t k = heap.size() - 1;
    size_t k2 = size_t((k-1)/2);

    while(k > k2 && heap.at(k).prio > heap.at(k2).prio)
    {
        Elem temp = heap.at(k);
        heap.at(k) = heap.at(k2);
        heap.at(k2) = temp;
        k = k2;
        k2 = size_t((k-1)/2);
    }
}

template <class T>
T PriorityQueue<T>::pop()
{
    if(heap.size() > 0)
    {
        T result = heap.front().data;

        size_t n = heap.size() - 1;
        size_t k = 0;
        heap.at(k) = heap.at(n);
        heap.pop_back();

        size_t kc = 1;

        while(kc < n)
        {
            if(kc+1 < n && heap.at(kc+1).prio > heap.at(kc).prio)
                kc += 1;

            if(heap.at(kc).prio > heap.at(k).prio)
            {
                Elem temp = heap.at(k);
                heap.at(k) = heap.at(kc);
                heap.at(kc) = temp;
            }

            k = kc;
            kc = 2*k + 1;
        }
        return result;
    }
}

template <class T>
T PriorityQueue<T>::front()
{
    return heap.front().data;
}
template <class T>
std::size_t PriorityQueue<T>::front_priority()
{
    return heap.front().prio;
}

template <class T>
size_t PriorityQueue<T>::size()
{
    return heap.size();
}
template <class T>
T PriorityQueue<T>::at(size_t index)
{
    return heap.at(index).data;
}
template <class T>
bool PriorityQueue<T>::empty()
{
    return heap.empty();
}



