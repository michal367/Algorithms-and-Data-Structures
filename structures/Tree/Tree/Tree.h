#ifndef TREE_H
#define TREE_H

#include <vector>
#include <iterator>
#include <stdexcept>
#include <stack>
#include <queue>

template <class T>
class Tree
{
    struct Node
    {
        T value;
        Node* parent;
        std::vector<Node*> children;
    };
    Node* root;

public:
    Tree();
    Tree(T val);
    Tree(const Tree<T>& other);
    Tree<T>& operator=(const Tree<T>& other);
    ~Tree();


    class iterator :public std::iterator<std::bidirectional_iterator_tag, T>
    {
        Node* ptr;
        friend Tree;
    public:
        iterator() : ptr(NULL) {}
        iterator(Node* p) : ptr(p) {}
        iterator(const iterator& other) : ptr(other.ptr) {}

        T& operator*() {return ptr->value;}
        T* operator->() {return &(ptr->value);}

        bool operator==(iterator b) {return ptr == b.ptr;}
        bool operator!=(iterator b) {return ptr != b.ptr;}

        iterator operator++()
        {
            if(!ptr->children.empty())
            {
                ptr = ptr->children.at(0);
                return *this;
            }
            else
                return NULL;
        }
        iterator operator--()
        {
            if(ptr != root)
            {
                ptr = ptr->parent;
                return *this;
            }
            else
                return NULL;
        }
        iterator operator++(int)
        {
            iterator clone(this);
            if(!ptr->children.empty())
                ptr = ptr->children.at(0);
            else
                ptr = NULL;
            return clone;
        }
        iterator operator--(int)
        {
            iterator clone(this);
            if(!ptr->children.empty())
                ptr = ptr->parent;
            else
                ptr = NULL;
            return clone;
        }
        iterator childAt(std::size_t index)
        {
            if(index > ptr->children.size()-1)
                throw std::out_of_range("Tree::iterator::at - index > ptr->children.size()-1");
            else
                return ptr->children.at(index);
        }
        iterator parent() {ptr = ptr->parent; return *this;}
        std::size_t outDegree() {return ptr->children.size();}
        std::size_t inDegree() {if(ptr->parent == NULL) return 0; else return 1;}
    };

    iterator begin() {return iterator(root);}
    iterator end() {return NULL;}


    void createRoot(const T val);

    iterator addChild(const T val, iterator node);
    void eraseNode(iterator node);

    Tree<T> subtree(iterator node);

    T& getRootValue();
    T& getNodeValue(iterator node);
    T& getChildValue(iterator node, std::size_t index = 0);

    bool isRoot(const iterator node);
    bool isLeaf(const iterator node);

    std::size_t height(iterator node);
    std::size_t depth(iterator node);

    std::size_t amountOfNodes(iterator node);
    std::size_t amountOfInnerNodes(iterator node);
    std::size_t amountOfLeaves(iterator node);

    bool empty();
    void clear();

    std::vector<T> preorder();
    std::vector<T> postorder();

    std::vector<T> preorderStack();
    std::vector<T> postorderStack();

    std::vector<T> BFS();

    void printTree();

private:
    void copyChildren(Node* destination_parent, Node* source_parent);
    void destroyNode(Node* node);

    void innerPreorder(Node* node, std::vector<T>& result);
    void innerPostorder(Node* node, std::vector<T>& result);

    void innerPrintTree(Node* node, std::string str = "", std::string str2 = "");
};


template <class T>
Tree<T>::Tree() : root(NULL) {}

template <class T>
Tree<T>::Tree(T val)
{
    root = new Node;
    root->value = val;
    root->parent = NULL;
}

template <class T>
Tree<T>::Tree(const Tree<T>& other)
{
    root = NULL;
    if(other.root != NULL)
    {
        createRoot(other.root->value);
        copyChildren(root, other.root);
    }
}
template <class T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other)
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
Tree<T>::~Tree()
{
    destroyNode(root);
}

template <class T>
void Tree<T>::createRoot(const T val)
{
    if(root == NULL)
    {
        root = new Node;
        root->value = val;
        root->parent = NULL;
    }
}


template <class T>
typename Tree<T>::iterator Tree<T>::addChild(const T val, iterator node)
{
    Node* new_node = new Node;
    new_node->value = val;
    new_node->parent = node.ptr;
    node.ptr->children.push_back(new_node);
    return new_node;
}
template <class T>
void Tree<T>::eraseNode(iterator node)
{
    if(node.ptr != root)
    {
        typename std::vector<Node*>::iterator it = node.ptr->parent->children.begin();
        for(; it != node.ptr->parent->children.end(); ++it)
            if(*it == node.ptr)
            {
                node.ptr->parent->children.erase(it);
                break;
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
Tree<T> Tree<T>::subtree(iterator node)
{
    Tree<T> result;
    result.createRoot(node.ptr->value);
    copyChildren(result.root, node.ptr);
    return result;
}

template <class T>
T& Tree<T>::getRootValue()
{
    if(root != NULL)
        return root->value;
}
template <class T>
T& Tree<T>::getNodeValue(iterator node)
{
    return node.ptr->value;
}
template <class T>
T& Tree<T>::getChildValue(iterator node, std::size_t index)
{
    return node.childAt(index).ptr->value;
}


template <class T>
bool Tree<T>::isRoot(iterator node)
{
    return node.ptr == root;
}
template <class T>
bool Tree<T>::isLeaf(iterator node)
{
    return node.ptr->children.empty();
}


template <class T>
std::size_t Tree<T>::height(iterator node)
{
    std::size_t height = 0;
    std::queue<Node*> nodes;
    nodes.push(node.ptr);
    nodes.push(NULL);
    while (!nodes.empty())
    {
        Node* n = nodes.front();
        nodes.pop();
        if (n == NULL)
        {
            if(!nodes.empty())
                nodes.push(NULL);

            ++height;
        }
        else
        {
            typename std::vector<Node*>::iterator it = n->children.begin();
            for(; it != n->children.end(); ++it)
                nodes.push(*it);
        }
    }
    return height-1;
}

template <class T>
std::size_t Tree<T>::depth(iterator node)
{
    std::size_t depth = 0;
    Node* it = node.ptr;
    while(it = it->parent)
        ++depth;
    return depth;
}

template <class T>
std::size_t Tree<T>::amountOfNodes(iterator node)
{
    std::size_t counter = 0;
    if(root != NULL)
    {
        std::stack<Node*> nodes;
        nodes.push(root);
        while(!nodes.empty())
        {
            Node* n = nodes.top();
            nodes.pop();

            typename std::vector<Node*>::iterator it = n->children.begin();
            for(; it != n->children.end(); ++it)
                nodes.push(*it);

            ++counter;
        }
    }
    return counter;
}
template <class T>
std::size_t Tree<T>::amountOfInnerNodes(iterator node)
{
    std::size_t counter = 0;
    if(root != NULL)
    {
        std::stack<Node*> nodes;
        nodes.push(root);
        while(!nodes.empty())
        {
            Node* n = nodes.top();
            nodes.pop();

            typename std::vector<Node*>::iterator it = n->children.begin();
            for(; it != n->children.end(); ++it)
                nodes.push(*it);

            if(!n->children.empty())
                ++counter;
        }
    }
    return counter;
}
template <class T>
std::size_t Tree<T>::amountOfLeaves(iterator node)
{
    std::size_t counter = 0;
    if(root != NULL)
    {
        std::stack<Node*> nodes;
        nodes.push(root);
        while(!nodes.empty())
        {
            Node* n = nodes.top();
            nodes.pop();

            typename std::vector<Node*>::iterator it = n->children.begin();
            for(; it != n->children.end(); ++it)
                nodes.push(*it);

            if(n->children.empty())
                ++counter;
        }
    }
    return counter;
}

template <class T>
bool Tree<T>::empty()
{
    return (root == NULL);
}
template <class T>
void Tree<T>::clear()
{
    destroyNode(root);
    root = NULL;
}


template <class T>
std::vector<T> Tree<T>::preorder(){
    std::vector<T> result;
    innerPreorder(root, result);
    return result;
}
template <class T>
void Tree<T>::innerPreorder(Node* node, std::vector<T>& result){
    if(node != NULL)
    {
        result.push_back(node->value);
        for(auto it = node->children.begin(); it != node->children.end(); it++)
            innerPreorder(*it, result);
    }
}
template <class T>
std::vector<T> Tree<T>::postorder(){
    std::vector<T> result;
    innerPostorder(root, result);
    return result;
}
template <class T>
void Tree<T>::innerPostorder(Node* node, std::vector<T>& result){
    if(node != NULL)
    {
        for(auto it = node->children.begin(); it != node->children.end(); it++)
            innerPostorder(*it, result);
        result.push_back(node->value);
    }
}


template <class T>
std::vector<T> Tree<T>::preorderStack(){
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
                for(auto it = node->children.rbegin(); it != node->children.rend(); it++)
                    nodes.push(*it);
            }
        }
    }
    return result;
}
template <class T>
std::vector<T> Tree<T>::postorderStack(){
    std::vector<T> result;
    if(root != NULL)
    {
        std::stack<Node*> nodes;
        nodes.push(root);
        Node* prev = NULL;
        while(!nodes.empty())
        {
            Node* node = nodes.top();

            bool going_down = false;
            if(prev != NULL)
                for(auto it = prev->children.begin(); it != prev->children.end(); it++)
                    if(*it == node){
                        going_down = true;
                        break;
                    }

            if(prev == NULL || going_down){
                if(node->children.size() > 0)
                    nodes.push(node->children.at(0));
            }
            else{
                std::size_t i=0;
                for(; i<node->children.size(); i++)
                    if(node->children.at(i) == prev)
                        break;
                if(i+1 < node->children.size()){
                    nodes.push(node->children.at(i+1));
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
std::vector<T> Tree<T>::BFS(){
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
                for(auto it = node->children.begin(); it != node->children.end(); it++)
                    nodes.push(*it);
            }
        }
    }
    return result;
}



template <class T>
void Tree<T>::copyChildren(Node* destination_parent, Node* source_parent)
{
    typename std::vector<Node*>::iterator it = source_parent->children.begin();
    for(; it != source_parent->children.end(); ++it)
        copyChildren(addChild((*it)->value, destination_parent).ptr, *it);
}

template <class T>
void Tree<T>::destroyNode(Node* node)
{
    if(node != NULL)
    {
        typename std::vector<Node*>::iterator it = node->children.begin();
        for(; it != node->children.end(); ++it)
            destroyNode(*it);
        delete node;
    }
}



template <class T>
void Tree<T>::printTree(){
    innerPrintTree(root);
}
template <class T>
void Tree<T>::innerPrintTree(Node* node, std::string str, std::string str2)
{
    if(node != NULL)
    {
        if(str2 == "")
        {
            std::cout << str << str2 << node->value << std::endl;
            for(int i=0; i<node->children.size(); ++i)
            {
                if(i < node->children.size()-1)
                    innerPrintTree(node->children.at(i), str, "\xc3\xc4");
                else
                    innerPrintTree(node->children.at(i), str, "\xc0\xc4");
            }
        }
        else
        {
            std::cout << str << str2 << node->value << std::endl;
            if(str2 == "\xc3\xc4")
            {
                for(int i=0; i<node->children.size(); ++i)
                {
                    if(i < node->children.size()-1)
                        innerPrintTree(node->children.at(i), str+"\xb3 ", "\xc3\xc4");
                    else
                        innerPrintTree(node->children.at(i), str+"\xb3 ", "\xc0\xc4");
                }
            }
            else
            {
                for(int i=0; i<node->children.size(); ++i)
                {
                    if(i < node->children.size()-1)
                        innerPrintTree(node->children.at(i), str+"  ", "\xc3\xc4");
                    else
                        innerPrintTree(node->children.at(i), str+"  ", "\xc0\xc4");
                }
            }
        }
    }
}


#endif // TREE_h
