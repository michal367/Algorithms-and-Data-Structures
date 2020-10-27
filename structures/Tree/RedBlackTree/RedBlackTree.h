#pragma once

#include <stack>
#include <stdexcept>
#include <iterator>
#include <iostream>

template <class T>
class RedBlackTree
{
    struct Node
    {
        T value;
        Node* parent;
        Node* left;
        Node* right;
        char color;
    };
    Node* root;

    Node* sentinel_node;

public:
    RedBlackTree();
    RedBlackTree(const T val);
    RedBlackTree(const RedBlackTree<T>& other);
    RedBlackTree<T>& operator=(const RedBlackTree<T>& other);
    ~RedBlackTree();

    class iterator :public std::iterator<std::bidirectional_iterator_tag, T>
    {
        Node* ptr;
        friend RedBlackTree;
    public:
        iterator() :ptr(NULL) {}
        iterator(Node* p) :ptr(p) {}
        iterator(const iterator& other) :ptr(other.ptr) {}

        T& operator*() {return ptr->value;}
        T* operator->() {return *(ptr->value);}

        char getColor() {return ptr->color;}

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
    void copyChildren(Node* destination_parent, Node* source_parent, Node* destination_sentinel, Node* source_sentinel);
    void destroyNode(Node* node);

    void createRoot(const T val);
    void createSentinelNode();
    Node* addLeftChild(const T val, Node* node);
    Node* addRightChild(const T val, Node* node);
    void eraseNode(iterator node);

    Node* minRBT(Node* node)
    {
      if(node != sentinel_node)
        while(node->left != sentinel_node) node = node->left;
      return node;
    }

    Node* succRBT(Node* node)
    {
      Node* r;
      if(node != sentinel_node)
      {
        if(node->right != sentinel_node) return minRBT(node->right);
        else
        {
          r = node->parent;
          while((r != sentinel_node) && (node == r->right))
          {
            node = r;
            r = r->parent;
          }
          return r;
        }
      }
      return sentinel_node;
    }

    void innerPrintTree(Node* node, std::string str = "", std::string str2 = "");
};


template <class T>
RedBlackTree<T>::RedBlackTree() :root(NULL), sentinel_node(NULL) {}

template <class T>
RedBlackTree<T>::RedBlackTree(const T val)
{
    root = new Node;
    root->value = val;
    sentinel_node = NULL;
    createSentinelNode();
    root->parent = NULL;
    root->left = sentinel_node;
    root->right = sentinel_node;
    root->color = 'B';
}

template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& other)
{
    root = NULL;
    sentinel_node = NULL;
    if(other.root != NULL)
    {
        createSentinelNode();
        createRoot(other.root->value);
        copyChildren(root, other.root, sentinel_node, other.sentinel_node);
    }
}
template <class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& other)
{
    if(this != &other)
    {
        if(root)
            destroyNode(root);
        root = NULL;
        sentinel_node = NULL;
        if(other.root != NULL)
        {
            createSentinelNode();
            createRoot(other.root->value);
            copyChildren(root, other.root, sentinel_node, other.sentinel_node);
        }
    }
    return *this;
}
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
    destroyNode(root);
}


template <class T>
void RedBlackTree<T>::add(const T val)
{
    if(root == NULL)
        createRoot(val);
    else
    {
        Node* ptr = root;
        Node* ptr_new;
        while(1)
        {
            if(val < ptr->value)
            {
                if(ptr->left != NULL && ptr->left != sentinel_node)
                    ptr = ptr->left;
                else
                {
                    ptr_new = addLeftChild(val, ptr);
                    break;
                }
            }
            else
            {
                if(ptr->right != NULL && ptr->right != sentinel_node)
                    ptr = ptr->right;
                else
                {
                    ptr_new = addRightChild(val, ptr);
                    break;
                }
            }
        }


        while(ptr->parent != NULL && ptr->color == 'R')
        {
            if(ptr->parent->left->color == 'R' && ptr->parent->right->color == 'R')
            {
                ptr->parent->left->color = 'B';
                ptr->parent->right->color = 'B';
                ptr->parent->color = 'R';
                if(ptr->parent == root)
                {
                    ptr->parent->color = 'B';
                    break;
                }
                ptr_new = ptr->parent;
                ptr = ptr->parent->parent;
            }
            else
            {
                if(ptr->parent->left->color == 'R' && ptr->parent->right->color == 'B' && ptr->right == ptr_new)
                {
                    rotateLeft(ptr);
                    ptr_new = ptr;
                    ptr = ptr->parent;
                }
                else if(ptr->parent->left->color == 'B' && ptr->parent->right->color == 'R' && ptr->left == ptr_new)
                {
                    rotateRight(ptr);
                    ptr_new = ptr;
                    ptr = ptr->parent;
                }
                if(ptr->parent->left->color == 'R' && ptr->parent->right->color == 'B' && ptr->left == ptr_new)
                {
                    rotateRight(ptr->parent);
                    ptr->color = 'B';
                    ptr->right->color = 'R';
                    break;
                }
                else if(ptr->parent->left->color == 'B' && ptr->parent->right->color == 'R' && ptr->right == ptr_new)
                {
                    rotateLeft(ptr->parent);
                    ptr->color = 'B';
                    ptr->left->color = 'R';
                    break;
                }
            }
        }
    }
}
template <class T>
typename RedBlackTree<T>::iterator RedBlackTree<T>::remove(typename RedBlackTree<T>::iterator node)
{
    Node* ptr = node.ptr;
    Node* ptr2;
    Node* ptr3;
    Node* ptr4;
    if(ptr->left == sentinel_node || ptr->right == sentinel_node)
        ptr2 = ptr;
    else
        ptr2 = succRBT(ptr);
    if(ptr2->left != sentinel_node)
        ptr3 = ptr2->left;
    else
        ptr3 = ptr2->right;
    ptr3->parent = ptr2->parent;

    if(ptr2->parent == sentinel_node)
        root = ptr3;
    else
    {
        if(ptr2 == ptr2->parent->left)
            ptr2->parent->left = ptr3;
        else
            ptr2->parent->right = ptr3;
    }

    if(ptr2 != ptr)
        ptr->value = ptr2->value;

    if(ptr2->color == 'B')
        while((ptr3 != root) && (ptr3->color == 'B'))
            if(ptr3 == ptr3->parent->left)
            {
                ptr4 = ptr3->parent->right;

                if(ptr4->color == 'R')
                {
                    ptr4->color = 'B';
                    ptr3->parent->color = 'R';
                    rotateLeft(ptr3->parent);
                    ptr4 = ptr3->parent->right;
                }
                if((ptr4->left->color == 'B') && (ptr4->right->color == 'B'))
                {
                    ptr4->color = 'R';
                    ptr3 = ptr3->parent;
                    continue;
                }
                if(ptr4->right->color == 'B')
                {
                    ptr4->left->color = 'B';
                    ptr4->color = 'R';
                    rotateRight(ptr4);
                    ptr4 = ptr3->parent->right;
                }
                ptr4->color = ptr3->parent->color;
                ptr3->parent->color = 'B';
                ptr4->right->color = 'B';
                rotateLeft(ptr3->parent);
                ptr3 = root;
            }
            else
            {
                ptr4 = ptr3->parent->left;

                if(ptr4->color == 'R')
                {
                    ptr4->color = 'B';
                    ptr3->parent->color = 'R';
                    rotateRight(ptr3->parent);
                    ptr4 = ptr3->parent->left;
                }
                if((ptr4->left->color == 'B') && (ptr4->right->color == 'B'))
                {
                    ptr4->color = 'R';
                    ptr3 = ptr3->parent;
                    continue;
                }
                if(ptr4->left->color == 'B')
                {
                    ptr4->right->color = 'B';
                    ptr4->color = 'R';
                    rotateLeft(ptr4);
                    ptr4 = ptr3->parent->left;
                }
                ptr4->color = ptr3->parent->color;
                ptr3->parent->color = 'B';
                ptr4->left->color = 'B';
                rotateRight(ptr3->parent);
                ptr3 = root;
            }

    ptr3->color = 'B';
    delete ptr2;

}

template <class T>
typename RedBlackTree<T>::iterator RedBlackTree<T>::find(T val)
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
bool RedBlackTree<T>::include(T val)
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
T RedBlackTree<T>::min()
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
T RedBlackTree<T>::max()
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
bool RedBlackTree<T>::empty()
{
    return (root == NULL);
}
template <class T>
void RedBlackTree<T>::clear()
{
    destroyNode(root);
    root = NULL;
}



template <class T>
void RedBlackTree<T>::rotateLeft(iterator node)
{
    Node* B = node.ptr->right;
    if(B != NULL && B != sentinel_node)
    {
        Node* p = node.ptr->parent;
        node.ptr->right = B->left;
        if(node.ptr->right != NULL && node.ptr->right != sentinel_node)
            node.ptr->right->parent = node.ptr;
        B->left = node.ptr;
        B->parent = p;
        node.ptr->parent = B;
        if(p == NULL || p == sentinel_node)
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
void RedBlackTree<T>::rotateRight(iterator node)
{
    Node* B = node.ptr->left;
    if(B != NULL && B != sentinel_node)
    {
        Node* p = node.ptr->parent;
        node.ptr->left = B->right;
        if(node.ptr->left != NULL && node.ptr->left != sentinel_node)
            node.ptr->left->parent = node.ptr;
        B->right = node.ptr;
        B->parent = p;
        node.ptr->parent = B;
        if(p == NULL || p == sentinel_node)
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



// ======================================

template <class T>
void RedBlackTree<T>::createRoot(const T val)
{
    if(root == NULL)
    {
        root = new Node;
        root->value = val;
        createSentinelNode();
        root->parent = NULL;
        root->left = sentinel_node;
        root->right = sentinel_node;
        root->color = 'B';
    }
}
template <class T>
void RedBlackTree<T>::createSentinelNode()
{
    if(sentinel_node == NULL)
    {
        sentinel_node = new Node;
        sentinel_node->parent = NULL;
        sentinel_node->left = NULL;
        sentinel_node->right = NULL;
        sentinel_node->value = 0;
        sentinel_node->color = 'B';
    }
}
template <class T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::addLeftChild(const T val, Node* node)
{
    if(node->left == NULL || node->left == sentinel_node)
    {
        node->left = new Node;
        node->left->value = val;
        node->left->left = sentinel_node;
        node->left->right = sentinel_node;
        node->left->parent = node;
        node->left->color = 'R';
        return node->left;
    }
    else
        throw std::out_of_range("RedBlackTree::addLeftChild: left child is assigned");
}
template <class T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::addRightChild(const T val, Node* node)
{
    if(node->right == NULL || node->right == sentinel_node)
    {
        node->right = new Node;
        node->right->value = val;
        node->right->left = sentinel_node;
        node->right->right = sentinel_node;
        node->right->parent = node;
        node->right->color = 'R';
        return node->right;
    }
    else
        throw std::out_of_range("RedBlackTree::addRightChild: right child is assigned");
}
template <class T>
void RedBlackTree<T>::eraseNode(iterator node)
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
void RedBlackTree<T>::copyChildren(Node* destination_parent, Node* source_parent, Node* destination_sentinel, Node* source_sentinel)
{
    if(source_parent->left != NULL){
        if(source_parent->left != source_sentinel)
            copyChildren(addLeftChild(source_parent->left->value, destination_parent), source_parent->left, destination_sentinel, source_sentinel);
        else
            destination_parent->left = destination_sentinel;
    }
    if(source_parent->right != NULL){
        if(source_parent->right != source_sentinel)
            copyChildren(addRightChild(source_parent->right->value, destination_parent), source_parent->right, destination_sentinel, source_sentinel);
        else
            destination_parent->right = destination_sentinel;
    }
}
template <class T>
void RedBlackTree<T>::destroyNode(Node* node)
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
void RedBlackTree<T>::printTree(){
    innerPrintTree(root);
}
template <class T>
void RedBlackTree<T>::innerPrintTree(Node* node, std::string str, std::string str2)
{
    if(node != NULL && node != sentinel_node)
    {
        if(str2 == "")
        {
            innerPrintTree(node->right, str, "\xda\xc4");
            std::cout << str << str2 << node->value << "(" << node->color << ")" << std::endl;
            innerPrintTree(node->left, str, "\xc0\xc4");
        }
        else
        {
            if(str2 == "\xc0\xc4")
            {
                innerPrintTree(node->right, str+"\xb3 ", "\xda\xc4");
                std::cout << str << str2 << node->value << "(" << node->color << ")" << std::endl;
                innerPrintTree(node->left, str+"  ", "\xc0\xc4");
            }
            else
            {
                innerPrintTree(node->right, str+"  ", "\xda\xc4");
                std::cout << str << str2 << node->value << "(" << node->color << ")" << std::endl;
                innerPrintTree(node->left, str+"\xb3 ", "\xc0\xc4");
            }
        }
    }
}
