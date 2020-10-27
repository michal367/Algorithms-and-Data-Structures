#pragma once

#include <iostream>
#include <sstream>

template<class T>
class Set{
    // set - Binary Search Tree (BST)

    struct Node{
        Node* left;
        Node* right;
        Node* parent;
        T value;
    };

    Node* root;
    std::size_t size;


public:
    Set();
    Set(std::initializer_list<T> il);
    Set(const Set<T>& other);
    Set<T>& operator=(const Set<T>& other);
    ~Set();

    std::size_t get_size();
    bool empty();
    void clear();

    void push(T value);
    void erase(T value);
    bool contains(T value) const;

    void sets_union(const Set<T>& other);
    void intersection(const Set<T>& other);
    void difference(const Set<T>& other);

    bool is_subset(const Set<T>& subset);

    void print_tree();

    void DSW();
    void rotateLeft(Node* node);
    void rotateRight(Node* node);

    template<class T2>
    friend std::ostream& operator<< (std::ostream& os, Set<T2>& set);

private:
    void delete_tree(Node* node);
    void copy_children(Node* destination_parent, Node* source_parent);
    void print_tree(Node* ptr, std::string str = "", std::string str2 = "");
    std::string get_tree_values(Node* node);

    Node* find(T value) const;
    void sets_union_recursive(Node* node);
    void intersection_recursive(Node* node, const Set<T>& other);
    void difference_recursive(Node* node);
    bool is_subset_recursive(Node* node);
};


template<class T>
Set<T>::Set() : root(nullptr), size(0) {}

template<class T>
Set<T>::Set(std::initializer_list<T> il) : Set() {
    for(auto it = il.begin(); it != il.end(); it++)
        push(*it);
}
template<class T>
Set<T>::Set(const Set<T>& other){
    root = new Node;
    root->parent = nullptr;
    root->left = nullptr;
    root->right = nullptr;
    root->value = other.root->value;

    size = other.size;

    copy_children(root, other.root);
}
template<class T>
Set<T>& Set<T>::operator=(const Set<T>& other){
    if(this != &other){
        delete_tree(root);

        root = new Node;
        root->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;
        root->value = other.root->value;

        size = other.size;

        copy_children(root, other.root);
    }
    return *this;
}
template<class T>
Set<T>::~Set(){
    delete_tree(root);
}
template<class T>
void Set<T>::delete_tree(Node* node){
    if(node != nullptr){
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}

template<class T>
std::size_t Set<T>::get_size(){
    return size;
}
template<class T>
bool Set<T>::empty(){
    return (size == 0);
}
template<class T>
void Set<T>::clear(){
    delete_tree(root);
    root = nullptr;
    size = 0;
}

template<class T>
void Set<T>::push(T value){
    if(root == nullptr){
        root = new Node;
        root->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;
        root->value = value;
        size = 1;
    }
    else{
        Node* p = root;
        Node* parent = nullptr;
        while(p != nullptr){
            parent = p;
            if(value < p->value)
                p = p->left;
            else if(value > p->value)
                p = p->right;
            else
                return;
        }

        Node* new_node = new Node;
        if(value < parent->value)
            parent->left = new_node;
        else
            parent->right = new_node;

        new_node->left = nullptr;
        new_node->right = nullptr;
        new_node->parent = parent;
        new_node->value = value;
        size++;
    }
}

template<class T>
void Set<T>::erase(T value){
    Node* ptr = find(value);
    if(ptr != nullptr)
    {
        Node* p = ptr->parent;
        Node* ptr2 = nullptr;
        if(ptr->left == nullptr && ptr->right == nullptr)
            ptr2 = nullptr;
        else if(ptr->left != nullptr && ptr->right == nullptr)
            ptr2 = ptr->left;
        else if(ptr->left == nullptr && ptr->right != nullptr)
            ptr2 = ptr->right;
        else if(ptr->left != nullptr && ptr->right != nullptr)
        {
            if(ptr->left->right != nullptr)
            {
                Node* p2 = ptr->left->right;
                while(p2->right != nullptr)
                    p2 = p2->right;

                p2->parent->right = p2->left;
                if(p2->left != nullptr)
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

        if(p == nullptr)
            root = ptr2;
        else
        {
            if(p->left == ptr)
                p->left = ptr2;
            else
                p->right = ptr2;
        }
        if(ptr2 != nullptr)
            ptr2->parent = p;

        delete ptr;
        size--;
    }
}

template<class T>
bool Set<T>::contains(T value) const{
    return (find(value) != nullptr);
}


template<class T>
typename Set<T>::Node* Set<T>::find(T value) const{
    Node* p = root;
    while(p != nullptr){
        if(value < p->value)
            p = p->left;
        else if(value > p->value)
            p = p->right;
        else
            return p;
    }
    return nullptr;
}



template<class T>
void Set<T>::sets_union(const Set<T>& other){
    sets_union_recursive(other.root);
}
template<class T>
void Set<T>::sets_union_recursive(Node* node){
    if(node != nullptr){
        push(node->value);
        sets_union_recursive(node->left);
        sets_union_recursive(node->right);
    }
}

template<class T>
void Set<T>::intersection(const Set<T>& other){
    intersection_recursive(root, other);
}
template<class T>
void Set<T>::intersection_recursive(Node* node, const Set<T>& other){
    if(node != nullptr){
        if(!other.contains(node->value))
            erase(node->value);
        intersection_recursive(node->left, other);
        intersection_recursive(node->right, other);
    }
}

template<class T>
void Set<T>::difference(const Set<T>& other){
    difference_recursive(other.root);
}
template<class T>
void Set<T>::difference_recursive(Node* node){
    if(node != nullptr){
        erase(node->value);
        difference_recursive(node->left);
        difference_recursive(node->right);
    }
}

template<class T>
bool Set<T>::is_subset(const Set<T>& subset){
    return is_subset_recursive(subset.root);
}
template<class T>
bool Set<T>::is_subset_recursive(Node* node){
    if(node != nullptr)
        return (contains(node->value) && is_subset_recursive(node->left) && is_subset_recursive(node->right));
    return true;
}






// ===========================================

template<class T>
void Set<T>::print_tree(){
    print_tree(root);
}

template<class T>
void Set<T>::print_tree(Node* ptr, std::string str, std::string str2){
    if(ptr != nullptr)
    {
        if(str2 == "")
        {
            print_tree(ptr->right, str, "\xda\xc4");
            std::cout << str << str2 << ptr->value << std::endl;
            print_tree(ptr->left, str, "\xc0\xc4");
        }
        else
        {
            if(str2 == "\xc0\xc4")
            {
                print_tree(ptr->right, str+"\xb3 ", "\xda\xc4");
                std::cout << str << str2 << ptr->value << std::endl;
                print_tree(ptr->left, str+"  ", "\xc0\xc4");
            }
            else
            {
                print_tree(ptr->right, str+"  ", "\xda\xc4");
                std::cout << str << str2 << ptr->value << std::endl;
                print_tree(ptr->left, str+"\xb3 ", "\xc0\xc4");
            }
        }
    }
}

template<class T>
std::ostream& operator<< (std::ostream& os, Set<T>& set)
{
    os << set.get_tree_values(set.root);
    return os;
}

template<class T>
std::string Set<T>::get_tree_values(Node* node){
    if(node != nullptr){
        std::stringstream ss;
        if(node->left != nullptr)
            ss << get_tree_values(node->left) << ' ';

        ss << node->value;

        if(node->right != nullptr)
            ss << ' ' << get_tree_values(node->right);

        return ss.str();
    }
    return "";
}

template<class T>
void Set<T>::copy_children(Node* destination_parent, Node* source_parent){
    if(source_parent != nullptr){
        Node* left = nullptr;
        if(source_parent->left != nullptr){
            left = new Node;
            destination_parent->left = left;
            left->parent = destination_parent;
            left->left = nullptr;
            left->right = nullptr;
            left->value = source_parent->left->value;
        }
        copy_children(left, source_parent->left);

        Node* right = nullptr;
        if(source_parent->right != nullptr){
            right = new Node;
            destination_parent->right = right;
            right->parent = destination_parent;
            right->left = nullptr;
            right->right = nullptr;
            right->value = source_parent->right->value;
        }
        copy_children(right, source_parent->right);
    }
}


// ==================================================

template <class T>
void Set<T>::rotateLeft(Node* node)
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
    }
}
template <class T>
void Set<T>::rotateRight(Node* node)
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
    }
}


template <class T>
void Set<T>::DSW()
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





