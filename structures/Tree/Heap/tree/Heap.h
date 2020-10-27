#pragma once

#include <stack>
#include <stdexcept>
#include <iterator>
#include <iostream>

template <class T>
class Heap
{
    struct Node
    {
        T value;
        Node* parent;
        Node* left;
        Node* right;
    };
    Node* root;

public:
    Heap();
    Heap(const T val);
    Heap(const Heap<T>& other);
    Heap<T>& operator=(const Heap<T>& other);
    ~Heap();

    class iterator :public std::iterator<std::bidirectional_iterator_tag, T>
    {
        Node* ptr;
        friend Heap;
    public:
        iterator() :ptr(NULL) {}
        iterator(Node* p) :ptr(p) {}
        iterator(const iterator& other) :ptr(other.ptr) {}

        T& operator*() {return ptr->value;}
        T* operator->() {return *(ptr->value);}

        bool operator==(const iterator b) {return (ptr == b.ptr);}
        bool operator!=(const iterator b) {return (ptr != b.ptr);}

        iterator operator++()
        {
            ptr = ptr->left;
            return *this;
        }
        iterator operator--()
        {
            ptr = ptr->parent;
            return *this;
        }
        iterator operator++(int)
        {
            iterator clone(ptr);
            ptr = ptr->left;
            return clone;
        }
        iterator operator--(int)
        {
            iterator clone(ptr);
            ptr = ptr->parent;
            return clone;
        }

        iterator childAt(std::size_t index = 0)
        {
            if(index == 0)
                return ptr->left;
            else if(index == 1)
                return ptr->right;
            else
                return NULL;
        }
        bool hasLeftChild() {return (ptr->left != NULL);}
        bool hasRightChild() {return (ptr->right != NULL);}
        bool hasParent() {return (ptr->parent != NULL);}

        iterator leftChild() {return ptr->left;}
        iterator rightChild() {return ptr->right;}
        iterator parent() {return ptr->parent;}
        std::size_t outDegree()
        {
            if(ptr->left != NULL && ptr->right != NULL)
                return 2;
            else if(ptr->left != NULL || ptr->right != NULL)
                return 1;
            else
                return 0;
        }
        std::size_t inDegree()
        {
            if(ptr->parent != NULL)
                return 1;
            else
                return 0;
        }
    };

    iterator begin() {return iterator(root);}
    iterator end() {return iterator(NULL);}


    void push(T value);
    T pop();
    iterator find(T val);
    bool include(T val);

    bool empty();
    void clear();

    void printTree();

private:
    void copyChildren(Node* destination_parent, Node* source_parent);
    void destroyNode(Node* node);

    Node* getParentOfAfterLastNode();
    Node* getLastNode();

    void createRoot(const T val);
    Node* addLeftChild(const T val, Node* node);
    Node* addRightChild(const T val, Node* node);

    void innerPrintTree(Node* node, std::string str = "", std::string str2 = "");
};


template <class T>
Heap<T>::Heap() :root(NULL) {}

template <class T>
Heap<T>::Heap(const T val)
{
    root = new Node;
    root->value = val;
    root->parent = NULL;
    root->left = NULL;
    root->right = NULL;
}

template <class T>
Heap<T>::Heap(const Heap<T>& other)
{
    root = NULL;
    if(other.root != NULL)
    {
        createRoot(other.root->value);
        copyChildren(root, other.root);
    }
}
template <class T>
Heap<T>& Heap<T>::operator=(const Heap<T>& other)
{
    if(this != &other)
    {
        if(root)
            destroyNode(root);
        root = NULL;
        if(other.root != NULL)
        {
            createRoot(other.root->value);
            copyChildren(root, other.root);
        }
    }
    return *this;
}
template <class T>
Heap<T>::~Heap()
{
    destroyNode(root);
}


template <class T>
void Heap<T>::push(T value)
{
    if(root == NULL)
        createRoot(value);
    else
    {
        Node* ptr = getParentOfAfterLastNode();
        Node* ptr_new;
        if(ptr->left == NULL)
            ptr_new = addLeftChild(value, ptr);
        else
            ptr_new = addRightChild(value, ptr);


        while(ptr_new->parent != NULL && ptr_new->value > ptr_new->parent->value)
        {
            T temp = ptr_new->value;
            ptr_new->value = ptr_new->parent->value;
            ptr_new->parent->value = temp;
            ptr_new = ptr_new->parent;
        }
    }
}
template <class T>
T Heap<T>::pop()
{
    if(root != NULL)
    {
        Node* ptr = getLastNode();
        if(ptr->parent != NULL)
        {
            if(ptr->parent->right == ptr)
                ptr->parent->right = NULL;
            else if(ptr->parent->left == ptr)
                ptr->parent->left = NULL;
        }

        T result = root->value;

        Node* ptr_root = root;
        if(root != ptr)
        {
            root = ptr;
            root->parent = NULL;
            if(ptr_root->left != ptr)
            {
                root->left = ptr_root->left;
                if(root->left != NULL)
                    root->left->parent = root;
            }
            else
                root->left = NULL;
            if(ptr_root->right != ptr)
            {
                root->right = ptr_root->right;
                if(root->right != NULL)
                    root->right->parent = root;
            }
            else
                root->right = NULL;
        }
        else
            root = NULL;
        delete ptr_root;

        Node* ptr3 = root;
        if(ptr3 != NULL)
            while(ptr3->left != NULL && ptr3->left->value > ptr3->value ||
                  ptr3->right != NULL && ptr3->right->value > ptr3->value)
            {
                if(ptr3->left != NULL && ptr3->left->value > ptr3->value &&
                   ptr3->right != NULL && ptr3->left->value >= ptr3->right->value ||
                   ptr3->left != NULL && ptr3->left->value > ptr3->value && ptr3->right == NULL)
                {
                    T temp = ptr3->value;
                    ptr3->value = ptr3->left->value;
                    ptr3->left->value = temp;
                    ptr3 = ptr3->left;
                }
                else if(ptr3->right != NULL && ptr3->right->value > ptr3->value &&
                        ptr3->left != NULL && ptr3->right->value > ptr3->left->value ||
                        ptr3->right != NULL && ptr3->right->value > ptr3->value && ptr3->right == NULL)
                {
                    T temp = ptr3->value;
                    ptr3->value = ptr3->right->value;
                    ptr3->right->value = temp;
                    ptr3 = ptr3->right;
                }
            }

        return result;
    }
}


template <class T>
bool Heap<T>::empty()
{
    return (root == NULL);
}
template <class T>
void Heap<T>::clear()
{
    destroyNode(root);
    root = NULL;
}




template <class T>
void Heap<T>::createRoot(const T val)
{
    if(root == NULL)
    {
        root = new Node;
        root->value = val;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
    }
}
template <class T>
typename Heap<T>::Node* Heap<T>::addLeftChild(const T val, Node* node)
{
    if(node->left == NULL)
    {
        node->left = new Node;
        node->left->value = val;
        node->left->left = NULL;
        node->left->right = NULL;
        node->left->parent = node;
        return node->left;
    }
    else
        throw std::out_of_range("Heap::addLeftChild: left child is assigned");
}
template <class T>
typename Heap<T>::Node* Heap<T>::addRightChild(const T val, Node* node)
{
    if(node->right == NULL)
    {
        node->right = new Node;
        node->right->value = val;
        node->right->left = NULL;
        node->right->right = NULL;
        node->right->parent = node;
        return node->right;
    }
    else
        throw std::out_of_range("Heap::addRightChild: right child is assigned");
}

template <class T>
typename Heap<T>::Node* Heap<T>::getParentOfAfterLastNode()
{
    Node* ptr = root;
    if(ptr != NULL)
    {
        while(ptr->left != NULL)
            ptr = ptr->left;

        Node* ptr2 = ptr;
        if(ptr2->parent != NULL)
        {
            ptr2 = ptr2->parent;
            if(ptr2->left == NULL || ptr2->right == NULL)
                return ptr2;
            while(ptr2 != NULL)
            {
                int i = 0;
                while(ptr2->parent != NULL && ptr2->parent->right == ptr2)
                {
                    ptr2 = ptr2->parent;
                    ++i;
                }
                ptr2 = ptr2->parent;
                if(ptr2 != NULL)
                {
                    ptr2 = ptr2->right;
                    for(; i>0; --i)
                        ptr2 = ptr2->left;
                    if(ptr2->left == NULL || ptr2->right == NULL)
                        return ptr2;
                }
            }
            return ptr;
        }
        else
            return ptr2;
    }
}


template <class T>
typename Heap<T>::Node* Heap<T>::getLastNode()
{
    Node* ptr = root;
    if(ptr != NULL)
    {
        while(ptr->left != NULL)
            ptr = ptr->left;

        if(ptr->parent != NULL)
        {
            Node* ptr2;
            while(ptr != NULL)
            {
                ptr2 = ptr;
                int i = 0;
                while(ptr->parent != NULL && ptr->parent->right == ptr)
                {
                    ptr = ptr->parent;
                    ++i;
                }
                ptr = ptr->parent;
                if(ptr != NULL)
                {
                    ptr = ptr->right;
                    for(; i>0; --i)
                        ptr = ptr->left;
                    if(ptr == NULL)
                        return ptr2;
                }
            }
            if(ptr == NULL)
                return ptr2;
        }
        else
            return ptr;
    }
}


template <class T>
void Heap<T>::copyChildren(Node* destination_parent, Node* source_parent)
{
    if(source_parent->left != NULL)
        copyChildren(addLeftChild(source_parent->left->value, destination_parent), source_parent->left);
    if(source_parent->right != NULL)
        copyChildren(addRightChild(source_parent->right->value, destination_parent), source_parent->right);
}
template <class T>
void Heap<T>::destroyNode(Node* node)
{
    if(node != NULL)
    {
        if(node->left != NULL)
            destroyNode(node->left);
        if(node->right != NULL)
            destroyNode(node->right);
        delete node;
    }
}



template <class T>
void Heap<T>::printTree(){
    innerPrintTree(root);
}
template <class T>
void Heap<T>::innerPrintTree(Node* node, std::string str, std::string str2)
{
    if(node != NULL)
    {
        if(str2 == "")
        {
            innerPrintTree(node->right, str, "\xda\xc4");
            std::cout << str << str2 << node->value << std::endl;
            innerPrintTree(node->left, str, "\xc0\xc4");
        }
        else
        {
            if(str2 == "\xc0\xc4")
            {
                innerPrintTree(node->right, str+"\xb3 ", "\xda\xc4");
                std::cout << str << str2 << node->value << std::endl;
                innerPrintTree(node->left, str+"  ", "\xc0\xc4");
            }
            else
            {
                innerPrintTree(node->right, str+"  ", "\xda\xc4");
                std::cout << str << str2 << node->value << std::endl;
                innerPrintTree(node->left, str+"\xb3 ", "\xc0\xc4");
            }
        }
    }
}
