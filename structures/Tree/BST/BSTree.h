#pragma once

#include <stack>
#include <stdexcept>
#include <iterator>

template <class T>
class BSTree
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
    BSTree();
    BSTree(const T val);
    BSTree(const BSTree<T>& other);
    BSTree<T>& operator=(const BSTree<T>& other);
    ~BSTree();

    class iterator :public std::iterator<std::bidirectional_iterator_tag, T>
    {
        Node* ptr;
        friend BSTree;
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


    void add(const T val);
    iterator remove(iterator node);
    iterator find(T val);
    bool include(T val);

    T min();
    T max();

    bool empty();
    void clear();

    void rotateLeft(iterator node);
    void rotateRight(iterator node);
    void DSW();

    //
    void in_order();

    void printTree();

private:
    void copyChildren(Node* destination_parent, Node* source_parent);
    void destroyNode(Node* node);

    void createRoot(const T val);
    iterator addLeftChild(const T val, iterator node);
    iterator addRightChild(const T val, iterator node);
    void eraseNode(iterator node);

    void innerPrintTree(Node* node, std::string str = "", std::string str2 = "");
};


template <class T>
BSTree<T>::BSTree() :root(NULL) {}

template <class T>
BSTree<T>::BSTree(const T val)
{
    root = new Node;
    root->value = val;
    root->parent = NULL;
    root->left = NULL;
    root->right = NULL;
}

template <class T>
BSTree<T>::BSTree(const BSTree<T>& other)
{
    root = NULL;
    if(other.root != NULL)
    {
        createRoot(other.root->value);
        copyChildren(root, other.root);
    }
}
template <class T>
BSTree<T>& BSTree<T>::operator=(const BSTree<T>& other)
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
BSTree<T>::~BSTree()
{
    destroyNode(root);
}


template <class T>
void BSTree<T>::add(const T val)
{
    if(root == NULL)
        createRoot(val);
    else
    {
        Node* ptr = root;
        while(1)
        {
            if(val < ptr->value)
            {
                if(ptr->left != NULL)
                    ptr = ptr->left;
                else
                {
                    addLeftChild(val, ptr);
                    return;
                }
            }
            else
            {
                if(ptr->right != NULL)
                    ptr = ptr->right;
                else
                {
                    addRightChild(val, ptr);
                    return;
                }
            }
        }
    }
}
template <class T>
typename BSTree<T>::iterator BSTree<T>::remove(typename BSTree<T>::iterator node)
{
    Node* ptr = node.ptr;
    if(ptr != NULL)
    {
        Node* p = ptr->parent;
        Node* ptr2 = NULL;
        if(ptr->left == NULL && ptr->right == NULL)
            ptr2 = NULL;
        else if(ptr->left != NULL && ptr->right == NULL)
            ptr2 = ptr->left;
        else if(ptr->left == NULL && ptr->right != NULL)
            ptr2 = ptr->right;
        else if(ptr->left != NULL && ptr->right != NULL)
        {
            if(ptr->left->right != NULL)
            {
                Node* p2 = ptr->left->right;
                while(p2->right != NULL)
                    p2 = p2->right;

                p2->parent->right = p2->left;
                if(p2->left != NULL)
                    p2->left->parent = p2->parent;

                ptr2 = p2;

                ptr2->left = ptr->left;
                ptr2->right = ptr->right;
                ptr2->left->parent = ptr2;
                ptr2->right->parent = ptr2;
            }
            else
            {
                ptr2 = ptr->left;
                ptr2->right = ptr->right;
                ptr2->right->parent = ptr2;
            }
        }

        if(p == NULL)
            root = ptr2;
        else
        {
            if(p->left == ptr)
                p->left = ptr2;
            else
                p->right = ptr2;
        }
        if(ptr2 != NULL)
            ptr2->parent = p;

        delete ptr;

        return ptr2;
    }
}

template <class T>
typename BSTree<T>::iterator BSTree<T>::find(T val)
{
    if(root == NULL)
        return NULL;
    else
    {
        Node* ptr = root;
        while(ptr != NULL)
        {
            if(ptr->value == val)
                return ptr;
            else if(val < ptr->value)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        return NULL;
    }
}
template <class T>
bool BSTree<T>::include(T val)
{
    if(root == NULL)
        return 0;
    else
    {
        Node* ptr = root;
        while(ptr != NULL)
        {
            if(ptr->value == val)
                return 1;
            else if(val < ptr->value)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        return 0;
    }
}


template <class T>
T BSTree<T>::min()
{
    if(root != NULL)
    {
        T result;
        Node* ptr = root;
        while(ptr->left != NULL)
            ptr = ptr->left;

        return ptr->value;
    }
}
template <class T>
T BSTree<T>::max()
{
    if(root != NULL)
    {
        T result;
        Node* ptr = root;
        while(ptr->right != NULL)
            ptr = ptr->right;

        return ptr->value;
    }
}

template <class T>
bool BSTree<T>::empty()
{
    return (root == NULL);
}
template <class T>
void BSTree<T>::clear()
{
    destroyNode(root);
    root = NULL;
}



template <class T>
void BSTree<T>::in_order()
{
    if(root != NULL)
    {
        std::stack<Node*> nodes;
        Node* ptr = root;
        while(!nodes.empty() || ptr != NULL)
        {
            if(ptr != NULL)
            {
                nodes.push(ptr);
                ptr = ptr->left;
            }
            else
            {
                ptr = nodes.top();
                nodes.pop();
                ptr = ptr->right;
            }
        }
    }
}

template <class T>
void BSTree<T>::rotateLeft(iterator node)
{
    Node* B = node.ptr->right;
    if(B != NULL)
    {
        Node* p = node.ptr->parent;
        node.ptr->right = B->left;
        if(node.ptr->right != NULL)
            node.ptr->right->parent = node.ptr;
        B->left = node.ptr;
        B->parent = p;
        node.ptr->parent = B;
        if(p == NULL)
            root = B;
        else
        {
            if(p->left == node.ptr)
                p->left = B;
            else
                p->right = B;
        }
    }
}
template <class T>
void BSTree<T>::rotateRight(iterator node)
{
    Node* B = node.ptr->left;
    if(B != NULL)
    {
        Node* p = node.ptr->parent;
        node.ptr->left = B->right;
        if(node.ptr->left != NULL)
            node.ptr->left->parent = node.ptr;
        B->right = node.ptr;
        B->parent = p;
        node.ptr->parent = B;
        if(p == NULL)
            root = B;
        else
        {
            if(p->left == node.ptr)
                p->left = B;
            else
                p->right = B;
        }
    }
}
template <class T>
void BSTree<T>::DSW()
{
    Node* node = root;
    std::size_t n = 0;
    while(node != NULL)
    {
        while(node->left != NULL)
        {
            rotateRight(node);
            node = node->parent;
        }
        node = node->right;
        ++n;
    }


    std::size_t x = n+1;
    std::size_t y = 1;
    x = x >> 1;
    while(x > 0)
    {
        y = y << 1;
        x = x >> 1;
    }
    std::size_t s = n+1-y;


    node = root;
    for(std::size_t i=0; i<s; i++)
    {
        rotateLeft(node);
        node = node->parent->right;
    }

    n -= s;
    while(n > 1)
    {
        n = n >> 1;
        node = root;
        for(std::size_t i=0; i<n; i++)
        {
            rotateLeft(node);
            node = node->parent->right;
        }
    }
}



// ======================================

template <class T>
void BSTree<T>::createRoot(const T val)
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
typename BSTree<T>::iterator BSTree<T>::addLeftChild(const T val, iterator node)
{
    if(!node.hasLeftChild())
    {
        node.ptr->left = new Node;
        node.ptr->left->value = val;
        node.ptr->left->left = NULL;
        node.ptr->left->right = NULL;
        node.ptr->left->parent = node.ptr;
        return iterator(node.ptr->left);
    }
    else
        throw std::out_of_range("BinaryTree::addChild: left child is assigned");
}
template <class T>
typename BSTree<T>::iterator BSTree<T>::addRightChild(const T val, iterator node)
{
    if(!node.hasRightChild())
    {
        node.ptr->right = new Node;
        node.ptr->right->value = val;
        node.ptr->right->left = NULL;
        node.ptr->right->right = NULL;
        node.ptr->right->parent = node.ptr;
        return iterator(node.ptr->right);
    }
    else
        throw std::out_of_range("BinaryTree::addChild: right child is assigned");
}
template <class T>
void BSTree<T>::eraseNode(iterator node)
{
    if(node.ptr != root)
    {
        if(node.ptr->parent != NULL)
        {
            if(node.ptr->parent->left == node.ptr)
                node.ptr->parent->left = NULL;
            else if(node.ptr->parent->right == node.ptr)
                node.ptr->parent->right = NULL;
        }
        destroyNode(node.ptr);
    }
    else
    {
        destroyNode(node.ptr);
        root = NULL;
    }
}


template <class T>
void BSTree<T>::copyChildren(Node* destination_parent, Node* source_parent)
{
    if(source_parent->left != NULL)
        copyChildren(addLeftChild(source_parent->left->value, destination_parent).ptr, source_parent->left);
    if(source_parent->right != NULL)
        copyChildren(addRightChild(source_parent->right->value, destination_parent).ptr, source_parent->right);
}
template <class T>
void BSTree<T>::destroyNode(Node* node)
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
void BSTree<T>::printTree(){
    innerPrintTree(root);
}
template <class T>
void BSTree<T>::innerPrintTree(Node* node, std::string str, std::string str2)
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
