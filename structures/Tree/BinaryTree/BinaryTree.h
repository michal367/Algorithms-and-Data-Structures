#pragma once

#include <iterator>
#include <stdexcept>
#include <stack>
#include <queue>

template <class T>
class BinaryTree
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
    BinaryTree();
    BinaryTree(const T val);
    BinaryTree(const BinaryTree<T>& other);
    BinaryTree<T> operator=(const BinaryTree<T>& other);
    ~BinaryTree();

    class iterator :public std::iterator<std::bidirectional_iterator_tag, T>
    {
        Node* ptr;
        friend BinaryTree;
    public:
        iterator() :ptr(NULL) {}
        iterator(Node* p) :ptr(p) {}
        iterator(const iterator& other) :ptr(other.ptr) {}

        T& operator*() {return ptr->value;}
        T& operator->() {return &(ptr->value);}

        bool operator==(iterator b) {return ptr == b.ptr;}
        bool operator!=(iterator b) {return ptr != b.ptr;}

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
            iterator clone(*this);
            ptr = ptr->left;
            return clone;
        }
        iterator operator--(int)
        {
            iterator clone(*this);
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
        bool hasLeftChild() {return ptr->left != NULL;}
        bool hasRightChild() {return ptr->right != NULL;}
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
    iterator end() {return NULL;}


    void createRoot(const T val);
    iterator addChild(const T val, iterator node);
    iterator addLeftChild(const T val, iterator node);
    iterator addRightChild(const T val, iterator node);
    void eraseNode(iterator node);

    BinaryTree<T> subtree(iterator node);

    T& getRootValue();
    T& getNodeValue(iterator node);
    T& getChildValue(iterator node, std::size_t index = 0);

    bool isRoot(iterator node);
    bool isLeaf(iterator node);

    std::size_t height(iterator node);
    std::size_t depth(iterator node);

    std::size_t amountOfNodes(iterator node);
    std::size_t amountOfInnerNodes(iterator node);
    std::size_t amountOfLeaves(iterator node);

    bool empty();
    void clear();

    std::vector<T> preorder();
    std::vector<T> inorder();
    std::vector<T> postorder();

    std::vector<T> preorderStack();
    std::vector<T> inorderStack();
    std::vector<T> postorderStack();

    std::vector<T> BFS();

    void printTree();

private:
    void copyChildren(Node* destination_parent, Node* source_parent);
    void destroyNode(Node* node);

    void innerPreorder(Node* node, std::vector<T>& result);
    void innerInorder(Node* node, std::vector<T>& result);
    void innerPostorder(Node* node, std::vector<T>& result);

    void innerPrintTree(Node* node, std::string str = "", std::string str2 = "");
};

template <class T>
BinaryTree<T>::BinaryTree() : root(NULL) {}
template <class T>
BinaryTree<T>::BinaryTree(const T val)
{
    root = new Node;
    root->value = val;
    root->parent = NULL;
    root->left = NULL;
    root->right = NULL;
}
template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
{
    root = NULL;
    if(other.root != NULL)
    {
        createRoot(other.root->value);
        copyChildren(root, other.root);
    }
}
template <class T>
BinaryTree<T> BinaryTree<T>::operator=(const BinaryTree<T>& other)
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
BinaryTree<T>::~BinaryTree()
{
    destroyNode(root);
}

template <class T>
BinaryTree<T> BinaryTree<T>::subtree(iterator node)
{
    BinaryTree<T> result;
    result.createRoot(node.ptr->value);
    result.copyChildren(result.root, node.ptr);
    return result;
}

template <class T>
void BinaryTree<T>::createRoot(const T val)
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
typename BinaryTree<T>::iterator BinaryTree<T>::addChild(const T val, iterator node)
{
    if(node.ptr->left == NULL)
    {
        node.ptr->left = new Node;
        node.ptr->left->value = val;
        node.ptr->left->parent = node.ptr;
        node.ptr->left->left = NULL;
        node.ptr->left->right = NULL;
        return iterator(node.ptr->left);
    }
    else if(node.ptr->right == NULL)
    {
        node.ptr->right = new Node;
        node.ptr->right->value = val;
        node.ptr->right->parent = node.ptr;
        node.ptr->right->left = NULL;
        node.ptr->right->right = NULL;
        return iterator(node.ptr->right);
    }
    else
        throw std::out_of_range("BinaryTree::addChild: left node and right node are assigned");
}
template <class T>
typename BinaryTree<T>::iterator BinaryTree<T>::addLeftChild(const T val, iterator node)
{
    if(node.ptr->left == NULL)
    {
        node.ptr->left = new Node;
        node.ptr->left->value = val;
        node.ptr->left->parent = node.ptr;
        node.ptr->left->left = NULL;
        node.ptr->left->right = NULL;
        return iterator(node.ptr->left);
    }
    else
        throw std::out_of_range("BinaryTree::addLeftChild: left node is assigned");
}
template <class T>
typename BinaryTree<T>::iterator BinaryTree<T>::addRightChild(const T val, iterator node)
{
    if(node.ptr->right == NULL)
    {
        node.ptr->right = new Node;
        node.ptr->right->value = val;
        node.ptr->right->parent = node.ptr;
        node.ptr->right->left = NULL;
        node.ptr->right->right = NULL;
        return iterator(node.ptr->right);
    }
    else
        throw std::out_of_range("BinaryTree::addRightChild: right node is assigned");
}

template <class T>
void BinaryTree<T>::eraseNode(iterator node)
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
T& BinaryTree<T>::getRootValue()
{
    if(root != NULL)
        return root->value;
}
template <class T>
T& BinaryTree<T>::getNodeValue(iterator node)
{
    return node.ptr->value;
}
template <class T>
T& BinaryTree<T>::getChildValue(iterator node, std::size_t index)
{
    if(index == 0)
        return node.ptr->left->value;
    else if(index == 1)
        return node.ptr->right->value;
    else
        throw std::out_of_range("BinaryTree::getChildValue: index > 1");
}

template <class T>
bool BinaryTree<T>::isRoot(iterator node)
{
    return node.ptr == root;
}
template <class T>
bool BinaryTree<T>::isLeaf(iterator node)
{
    return (node.ptr->left == NULL && node.ptr->right == NULL);
}

template <class T>
std::size_t BinaryTree<T>::height(iterator node)
{
    std::size_t height = 0;
    std::queue<Node*> nodes;
    nodes.push(node.ptr);
    nodes.push(NULL);
    while(!nodes.empty())
    {
        Node* n = nodes.front();
        nodes.pop();
        if(n != NULL)
        {
            if(n->left != NULL)
                nodes.push(n->left);
            if(n->right != NULL)
                nodes.push(n->right);
        }
        else
        {
            if(!nodes.empty())
                nodes.push(NULL);
            ++height;
        }
    }
    return height-1;
}
template <class T>
std::size_t BinaryTree<T>::depth(iterator node)
{
    std::size_t depth = 0;
    Node* it = node.ptr;
    while(it = it->parent)
        ++depth;
    return depth;
}

template <class T>
std::size_t BinaryTree<T>::amountOfNodes(iterator node)
{
    std::size_t counter = 0;
    if(node != NULL)
    {
        std::stack<Node*> nodes;
        nodes.push(node.ptr);
        while(!nodes.empty())
        {
            Node* n = nodes.top();
            nodes.pop();

            if(n->left != NULL)
                nodes.push(n->left);
            if(n->right != NULL)
                nodes.push(n->right);

            std::cout << n->value << " | ";

            ++counter;
        }
    }
    return counter;
}
template <class T>
std::size_t BinaryTree<T>::amountOfInnerNodes(iterator node)
{
    std::size_t counter = 0;
    if(node.ptr != NULL)
    {
        std::stack<Node*> nodes;
        nodes.push(node.ptr);
        while(!nodes.empty())
        {
            Node* n = nodes.top();
            nodes.pop();

            if(n->left != NULL)
                nodes.push(n->left);
            if(n->right != NULL)
                nodes.push(n->right);

            if(n->left != NULL || n->right != NULL)
                ++counter;
        }
    }
    return counter;
}
template <class T>
std::size_t BinaryTree<T>::amountOfLeaves(iterator node)
{
    std::size_t counter = 0;
    if(node.ptr != NULL)
    {
        std::stack<Node*> nodes;
        nodes.push(node.ptr);
        while(!nodes.empty())
        {
            Node* n = nodes.top();
            nodes.pop();

            if(n->left != NULL)
                nodes.push(n->left);
            if(n->right != NULL)
                nodes.push(n->right);
            if(n->left == NULL && n->right == NULL)
                ++counter;
        }
    }
    return counter;
}


template <class T>
bool BinaryTree<T>::empty()
{
    return (root == NULL);
}
template <class T>
void BinaryTree<T>::clear()
{
    destroyNode(root);
    root = NULL;
}


template <class T>
std::vector<T> BinaryTree<T>::preorder(){
    std::vector<T> result;
    innerPreorder(root, result);
    return result;
}
template <class T>
void BinaryTree<T>::innerPreorder(Node* node, std::vector<T>& result){
    if(node != NULL)
    {
        result.push_back(node->value);
        innerPreorder(node->left, result);
        innerPreorder(node->right, result);
    }
}
template <class T>
std::vector<T> BinaryTree<T>::inorder(){
    std::vector<T> result;
    innerInorder(root, result);
    return result;
}
template <class T>
void BinaryTree<T>::innerInorder(Node* node, std::vector<T>& result){
    if(node != NULL)
    {
        innerInorder(node->left, result);
        result.push_back(node->value);
        innerInorder(node->right, result);
    }
}
template <class T>
std::vector<T> BinaryTree<T>::postorder(){
    std::vector<T> result;
    innerPostorder(root, result);
    return result;
}
template <class T>
void BinaryTree<T>::innerPostorder(Node* node, std::vector<T>& result){
    if(node != NULL)
    {
        innerPostorder(node->left, result);
        innerPostorder(node->right, result);
        result.push_back(node->value);
    }
}

template <class T>
std::vector<T> BinaryTree<T>::preorderStack(){
    std::vector<T> result;
    if(root != NULL)
    {
        std::stack<Node*> nodes;
        nodes.push(root);
        while(!nodes.empty())
        {
            Node* node = nodes.top();
            nodes.pop();

            if(node != NULL)
            {
                result.push_back(node->value);
                nodes.push(node->right);
                nodes.push(node->left);
            }
        }
    }
    return result;
}
template <class T>
std::vector<T> BinaryTree<T>::inorderStack(){
    std::vector<T> result;
    if(root != NULL)
    {
        std::stack<Node*> nodes;
        Node* cur = root;
        while(!nodes.empty() || cur != NULL)
        {
            if(cur != NULL){
                nodes.push(cur);
                cur = cur->left;
            }
            else{
                cur = nodes.top();
                nodes.pop();
                result.push_back(cur->value);
                cur = cur->right;
            }
        }
    }
    return result;
}
template <class T>
std::vector<T> BinaryTree<T>::postorderStack(){
    std::vector<T> result;
    if(root != NULL)
    {
        std::stack<Node*> nodes;
        nodes.push(root);
        Node* prev = NULL;
        while(!nodes.empty())
        {
            Node* node = nodes.top();

            if(prev == NULL || prev->left == node || prev->right == node){
                if(node->left != NULL)
                    nodes.push(node->left);
                else if(node->right != NULL)
                    nodes.push(node->right);
            }
            else{
                if(node->left == prev){
                    if(node->right != NULL)
                        nodes.push(node->right);
                }
                else{
                    result.push_back(node->value);
                    nodes.pop();
                }
            }
            prev = node;
        }
    }
    return result;
}


template <class T>
std::vector<T> BinaryTree<T>::BFS(){
    std::vector<T> result;
    if(root != NULL)
    {
        std::queue<Node*> nodes;
        nodes.push(root);
        while(!nodes.empty())
        {
            Node* node = nodes.front();
            nodes.pop();

            if(node != NULL)
            {
                result.push_back(node->value);
                nodes.push(node->left);
                nodes.push(node->right);
            }
        }
    }
    return result;
}


template <class T>
void BinaryTree<T>::copyChildren(Node* destination_parent, Node* source_parent)
{
    if(source_parent->left != NULL)
        copyChildren(addLeftChild(source_parent->left->value, destination_parent).ptr, source_parent->left);
    if(source_parent->right != NULL)
        copyChildren(addRightChild(source_parent->right->value, destination_parent).ptr, source_parent->right);
}
template <class T>
void BinaryTree<T>::destroyNode(Node* node)
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
void BinaryTree<T>::printTree(){
    innerPrintTree(root);
}
template <class T>
void BinaryTree<T>::innerPrintTree(Node* node, std::string str, std::string str2)
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
