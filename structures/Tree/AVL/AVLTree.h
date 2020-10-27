#pragma once

#include <stack>
#include <stdexcept>
#include <iterator>
#include <string>
#include <iostream>

template <class T>
class AVLTree
{
    struct Node
    {
        T value;
        Node* parent;
        Node* left;
        Node* right;
        int bf; // height of left subtree minus height of right subtree
    };
    Node* root;

public:
    AVLTree();
    AVLTree(const T val);
    AVLTree(const AVLTree<T>& other);
    AVLTree<T>& operator=(const AVLTree<T>& other);
    ~AVLTree();

    class iterator :public std::iterator<std::bidirectional_iterator_tag, T>
    {
        Node* ptr;
        friend AVLTree;
    public:
        iterator() :ptr(NULL) {}
        iterator(Node* p) :ptr(p) {}
        iterator(const iterator& other) :ptr(other.ptr) {}

        T& operator*() {return ptr->value;}
        T* operator->() {return *(ptr->value);}

        int getBf() {return ptr->bf;}

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

    //
    void in_order();

    void printTree();

private:
    void copyChildren(Node* destination_parent, Node* source_parent);
    void destroyNode(Node* node);

    void createRoot(const T val);
    Node* addLeftChild(const T val, Node* node, int bf=0);
    Node* addRightChild(const T val, Node* node, int bf=0);

    void rotationRR(Node* node);
    void rotationLL(Node* node);
    void rotationRL(Node* node);
    void rotationLR(Node* node);

    Node* predAVL(Node* p)
    {
      Node* r;

      if(p)
      {
        if(p->left)
        {
          p = p->left;
          while(p->right) p = p->right;
        }
        else
          do
          {
            r = p;
            p = p->parent;
          } while(p && p->right != r);
      }
      return p;
    }

    void innerPrintTree(Node* node, std::string str = "", std::string str2 = "");
};


template <class T>
AVLTree<T>::AVLTree() :root(NULL) {}

template <class T>
AVLTree<T>::AVLTree(const T val)
{
    root = new Node;
    root->value = val;
    root->parent = NULL;
    root->left = NULL;
    root->right = NULL;
    root->bf = 0;
}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T>& other)
{
    root = NULL;
    if(other.root != NULL)
    {
        createRoot(other.root->value);
        root->bf = other.root->bf;
        copyChildren(root, other.root);
    }
}
template <class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& other)
{
    if(this != &other)
    {
        if(root)
            destroyNode(root);
        root = NULL;
        if(other.root != NULL)
        {
            createRoot(other.root->value);
            root->bf = other.root->bf;
            copyChildren(root, other.root);
        }
    }
    return *this;
}
template <class T>
AVLTree<T>::~AVLTree()
{
    destroyNode(root);
}


template <class T>
void AVLTree<T>::add(const T val)
{
    if(root == NULL)
        createRoot(val);
    else
    {
        Node* ptr = root;
        Node* ptr2;
        while(1)
        {
            if(val < ptr->value)
            {
                if(ptr->left != NULL)
                    ptr = ptr->left;
                else
                {
                    ptr2 = addLeftChild(val, ptr);
                    break;
                }
            }
            else
            {
                if(ptr->right != NULL)
                    ptr = ptr->right;
                else
                {
                    ptr2 = addRightChild(val, ptr);
                    break;
                }
            }
        }

        if(ptr->bf == 0)
        {
            if(ptr->left == ptr2)
                ptr->bf = 1;
            else
                ptr->bf = -1;

            Node* ptr3 = ptr->parent;
            while(ptr3 != NULL)
            {
                if(ptr3->bf != 0)
                {
                    if(ptr3->bf == -1)
                    {
                        if(ptr3->left == ptr)
                        {
                            ptr3->bf = 0;
                            return;
                        }
                        if(ptr->bf == 1)
                            rotationRL(ptr3);
                        else
                            rotationRR(ptr3);
                        return;
                    }
                    if(ptr3->right == ptr)
                    {
                        ptr3->bf = 0;
                        return;
                    }
                    if(ptr->bf == -1)
                        rotationLR(ptr3);
                    else
                        rotationLL(ptr3);
                    return;
                }
                if(ptr3->left == ptr)
                    ptr3->bf = 1;
                else
                    ptr3->bf = -1;
                ptr = ptr3;
                ptr3 = ptr3->parent;
            }
        }
        else
            ptr->bf = 0;
    }
}

template <class T>
typename AVLTree<T>::iterator AVLTree<T>::remove(typename AVLTree<T>::iterator node)
{
    Node* ptr = node.ptr;
    if(ptr != NULL)
    {
        bool nest;
        Node* ptr2;
        if(ptr->left == NULL || ptr->right == NULL)
        {
            if(ptr->left != NULL)
            {
                ptr2 = ptr->left;
                ptr->left = NULL;
            }
            else
            {
                ptr2 = ptr->right;
                ptr->right = NULL;
            }
            ptr->bf = 0;
            nest = true;
        }
        else
        {
            ptr2 = remove(predAVL(ptr)).ptr;
            nest = false;
        }

        if(ptr2 != NULL)
        {
            ptr2->parent = ptr->parent;
            ptr2->left = ptr->left;
            if(ptr2->left != NULL)
                ptr2->left->parent = ptr2;
            ptr2->right = ptr->right;
            if(ptr2->right != NULL)
                ptr2->right->parent = ptr2;
            ptr2->bf = ptr->bf;
        }

        if(ptr->parent == NULL)
        {
            root = ptr2;
        }
        else
        {
            if(ptr->parent->left == ptr)
                ptr->parent->left = ptr2;
            else
                ptr->parent->right = ptr2;
        }
        if(nest)
        {
            Node* ptr3 = ptr2;
            ptr2 = ptr->parent;
            while(ptr2 != NULL)
            {
                if(ptr2->bf != 0)
                {
                    if((ptr2->bf != 1 || ptr2->left != ptr3) &&
                       (ptr2->bf != -1 || ptr2->right != ptr3))
                    {
                        Node* ptr4;
                        if(ptr2->left == ptr3)
                            ptr4 = ptr2->right;
                        else
                            ptr4 = ptr2->left;
                        if(ptr4->bf == 0)
                        {
                            if(ptr2->bf == 1)
                                rotationLL(ptr2);
                            else
                                rotationRR(ptr2);
                            break;
                        }
                        else if(ptr2->bf == ptr4->bf)
                        {
                            if(ptr2->bf == 1)
                                rotationLL(ptr2);
                            else
                                rotationRR(ptr2);
                            ptr3 = ptr4;
                            ptr2 = ptr4->parent;
                        }
                        else
                        {
                            if(ptr2->bf == 1)
                                rotationLR(ptr2);
                            else
                                rotationRL(ptr2);
                            ptr3 = ptr2->parent;
                            ptr2 = ptr3->parent;
                        }

                    }
                    else
                    {
                        ptr2->bf = 0;
                        ptr3 = ptr2;
                        ptr2 = ptr2->parent;
                    }
                }
                else
                {
                    if(ptr2->left == ptr3)
                        ptr2->bf = -1;
                    break;
                }
            }
            return ptr;
        }
        else
            return ptr;
    }
}


template <class T>
typename AVLTree<T>::iterator AVLTree<T>::find(T val)
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
bool AVLTree<T>::include(T val)
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
T AVLTree<T>::min()
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
T AVLTree<T>::max()
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
bool AVLTree<T>::empty()
{
    return (root == NULL);
}
template <class T>
void AVLTree<T>::clear()
{
    destroyNode(root);
    root = NULL;
}



template <class T>
void AVLTree<T>::in_order()
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
                std::cout << ptr->value << ' ';
                ptr = ptr->right;
            }
        }
    }
}





// ======================================

template <class T>
void AVLTree<T>::createRoot(const T val)
{
    if(root == NULL)
    {
        root = new Node;
        root->value = val;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        root->bf = 0;
    }
}
template <class T>
typename AVLTree<T>::Node* AVLTree<T>::addLeftChild(const T val, Node* node, int bf)
{
    if(node->left == NULL)
    {
        node->left = new Node;
        node->left->value = val;
        node->left->left = NULL;
        node->left->right = NULL;
        node->left->parent = node;
        node->left->bf = bf;
        return node->left;
    }
    else
        throw std::out_of_range("BinaryTree::addChild: left child is assigned");
}
template <class T>
typename AVLTree<T>::Node* AVLTree<T>::addRightChild(const T val, Node* node, int bf)
{
    if(node->right == NULL)
    {
        node->right = new Node;
        node->right->value = val;
        node->right->left = NULL;
        node->right->right = NULL;
        node->right->parent = node;
        node->right->bf = bf;
        return node->right;
    }
    else
        throw std::out_of_range("BinaryTree::addChild: right child is assigned");
}


template <class T>
void AVLTree<T>::copyChildren(Node* destination_parent, Node* source_parent)
{
    if(source_parent->left != NULL)
        copyChildren(addLeftChild(source_parent->left->value, destination_parent, source_parent->left->bf), source_parent->left);
    if(source_parent->right != NULL)
        copyChildren(addRightChild(source_parent->right->value, destination_parent, source_parent->right->bf), source_parent->right);
}
template <class T>
void AVLTree<T>::destroyNode(Node* node)
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
void AVLTree<T>::rotationRR(Node* node)
{
    Node* B = node->right;
    if(B != NULL)
    {
        Node* p = node->parent;
        node->right = B->left;
        if(node->right != NULL)
            node->right->parent = node;
        B->left = node;
        B->parent = p;
        node->parent = B;
        if(p == NULL)
            root = B;
        else
        {
            if(p->left == node)
                p->left = B;
            else
                p->right = B;
        }

        if(B->bf == -1)
        {
            B->bf = 0;
            node->bf = 0;
        }
        else
        {
            B->bf = 1;
            node->bf = -1;
        }
    }
}
template <class T>
void AVLTree<T>::rotationLL(Node* node)
{
    Node* B = node->left;
    if(B != NULL)
    {
        Node* p = node->parent;
        node->left = B->right;
        if(node->left != NULL)
            node->left->parent = node;
        B->right = node;
        B->parent = p;
        node->parent = B;
        if(p == NULL)
            root = B;
        else
        {
            if(p->left == node)
                p->left = B;
            else
                p->right = B;
        }

        if(B->bf == 1)
        {
            B->bf = 0;
            node->bf = 0;
        }
        else
        {
            B->bf = -1;
            node->bf = 1;
        }
    }
}
template <class T>
void AVLTree<T>::rotationRL(Node* node)
{
    Node* B = node->right;
    if(B != NULL)
    {
        Node* C = B->left;
        if(C != NULL)
        {
            node->right = C->left;
            if(C->left != NULL)
                C->left->parent = node;
            C->left = node;

            B->left = C->right;
            if(C->right != NULL)
                C->right->parent = B;
            C->right = B;

            Node* p = node->parent;
            node->parent = C;
            B->parent = C;
            C->parent = p;

            if(p == NULL)
                root = C;
            else
            {
                if(p->left == node)
                    p->left = C;
                else
                    p->right = C;
            }

            if(C->bf == -1)
                node->bf = 1;
            else
                node->bf = 0;
            if(C->bf == 1)
                B->bf = -1;
            else
                B->bf = 0;
            C->bf = 0;
        }
    }
}
template <class T>
void AVLTree<T>::rotationLR(Node* node)
{
    Node* B = node->left;
    if(B != NULL)
    {
        Node* C = B->right;
        if(C != NULL)
        {
            node->left = C->right;
            if(C->right != NULL)
                C->right->parent = node;
            C->right = node;

            B->right = C->left;
            if(C->left != NULL)
                C->left->parent = B;
            C->left = B;

            Node* p = node->parent;
            node->parent = C;
            B->parent = C;
            C->parent = p;
            if(p == NULL)
                root = C;
            else
            {
                if(p->left == node)
                    p->left = C;
                else
                    p->right = C;
            }

            if(C->bf == 1)
                node->bf = -1;
            else
                node->bf = 0;
            if(C->bf == -1)
                B->bf = 1;
            else
                B->bf = 0;
            C->bf = 0;
        }
    }
}



template <class T>
void AVLTree<T>::printTree(){
    innerPrintTree(root);
}
template <class T>
void AVLTree<T>::innerPrintTree(Node* node, std::string str, std::string str2)
{
    if(node != NULL)
    {
        if(str2 == "")
        {
            innerPrintTree(node->right, str, "\xda\xc4");
            std::cout << str << str2 << node->value << "(" << node->bf << ")" << std::endl;
            innerPrintTree(node->left, str, "\xc0\xc4");
        }
        else
        {
            if(str2 == "\xc0\xc4")
            {
                innerPrintTree(node->right, str+"\xb3 ", "\xda\xc4");
                std::cout << str << str2 << node->value << "(" << node->bf << ")" << std::endl;
                innerPrintTree(node->left, str+"  ", "\xc0\xc4");
            }
            else
            {
                innerPrintTree(node->right, str+"  ", "\xda\xc4");
                std::cout << str << str2 << node->value << "(" << node->bf << ")" << std::endl;
                innerPrintTree(node->left, str+"\xb3 ", "\xc0\xc4");
            }
        }
    }
}
