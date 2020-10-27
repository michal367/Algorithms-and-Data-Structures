#pragma once

#include <iterator>
#include <stdexcept>
#include <stack>
#include <queue>
#include "MathParser.h"

class ExpressionTree
{
    struct Node
    {
        std::string value;
        Node* parent;
        Node* left;
        Node* right;
    };
    Node* root;

public:
    ExpressionTree();
    ExpressionTree(const std::string expression);
    ExpressionTree(const ExpressionTree& other);
    ExpressionTree operator=(const ExpressionTree& other);
    ~ExpressionTree();

    class iterator :public std::iterator<std::bidirectional_iterator_tag, std::string>
    {
        Node* ptr;
        friend ExpressionTree;
    public:
        iterator() :ptr(nullptr) {}
        iterator(Node* p) :ptr(p) {}
        iterator(const iterator& other) :ptr(other.ptr) {}

        std::string& operator*() {return ptr->value;}
        //string& operator->() {return &(ptr->value);}

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
                return nullptr;
        }
        bool hasLeftChild() {return ptr->left != nullptr;}
        bool hasRightChild() {return ptr->right != nullptr;}
        iterator leftChild() {return ptr->left;}
        iterator rightChild() {return ptr->right;}
        iterator parent() {return ptr->parent;}
        std::size_t outDegree()
        {
            if(ptr->left != nullptr && ptr->right != nullptr)
                return 2;
            else if(ptr->left != nullptr || ptr->right != nullptr)
                return 1;
            else
                return 0;
        }
        std::size_t inDegree()
        {
            if(ptr->parent != nullptr)
                return 1;
            else
                return 0;
        }
    };

    iterator begin() {return iterator(root);}
    iterator end() {return nullptr;}

    void createRoot(const std::string val);
    iterator addChild(const std::string val, iterator node);
    iterator addLeftChild(const std::string val, iterator node);
    iterator addRightChild(const std::string val, iterator node);
    void eraseNode(iterator node);

    ExpressionTree subtree(iterator node);

    std::string& getRootValue();
    std::string& getNodeValue(iterator node);
    std::string& getChildValue(iterator node, std::size_t index = 0);

    bool isRoot(iterator node);
    bool isLeaf(iterator node);

    bool empty();
    void clear();

    void printTree();

private:
    void copyChildren(Node* destination_parent, Node* source_parent);
    void destroyNode(Node* node);
    Node* createNode(const std::string val);

    void innerPrintTree(Node* node, std::string str = "", std::string str2 = "");
};

ExpressionTree::ExpressionTree() : root(nullptr) {}
ExpressionTree::ExpressionTree(const std::string expression)
{
    std::string RPN = MathParser::toRPN(expression);
    std::vector<std::string> exprs = MathParser::split(RPN, " ");

    std::stack<Node*> nodes;

    for(std::vector<std::string>::iterator it = exprs.begin(); it != exprs.end(); ++it)
    {
        if(MathParser::is_binary_operator(*it))
        {
            Node* op = createNode(*it);
            Node* a = nodes.top();
            nodes.pop();
            Node* b = nodes.top();
            nodes.pop();

            op->left = b;
            op->right = a;
            a->parent = op;
            b->parent = op;

            nodes.push(op);
        }
        else if(MathParser::is_unary_operator(*it))
        {
            Node* op = createNode(*it);
            Node* a = nodes.top();
            nodes.pop();

            op->left = a;
            a->parent = op;

            nodes.push(op);
        }
        else
        {
            nodes.push(createNode(*it));
        }
    }
    if(!nodes.empty())
        root = nodes.top();
    else
        root = nullptr;
}
ExpressionTree::ExpressionTree(const ExpressionTree& other)
{
    root = nullptr;
    if(other.root != nullptr)
    {
        createRoot(other.root->value);
        copyChildren(root, other.root);
    }
}
ExpressionTree ExpressionTree::operator=(const ExpressionTree& other)
{
    if(this != &other)
    {
        if(root != nullptr)
            destroyNode(root);
        root = nullptr;
        if(other.root != nullptr)
        {
            createRoot(other.root->value);
            copyChildren(root, other.root);
        }
    }
    return *this;
}
ExpressionTree::~ExpressionTree()
{
    destroyNode(root);
}

ExpressionTree ExpressionTree::subtree(iterator node)
{
    ExpressionTree result;
    result.createRoot(node.ptr->value);
    result.copyChildren(result.root, node.ptr);
    return result;
}


void ExpressionTree::createRoot(const std::string val)
{
    if(root == nullptr)
    {
        root = new Node;
        root->value = val;
        root->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;
    }
}
ExpressionTree::iterator ExpressionTree::addChild(const std::string val, iterator node)
{
    if(node.ptr->left == nullptr)
    {
        node.ptr->left = new Node;
        node.ptr->left->value = val;
        node.ptr->left->parent = node.ptr;
        node.ptr->left->left = nullptr;
        node.ptr->left->right = nullptr;
        return iterator(node.ptr->left);
    }
    else if(node.ptr->right == nullptr)
    {
        node.ptr->right = new Node;
        node.ptr->right->value = val;
        node.ptr->right->parent = node.ptr;
        node.ptr->right->left = nullptr;
        node.ptr->right->right = nullptr;
        return iterator(node.ptr->right);
    }
    else
        throw std::out_of_range("ExpressionTree::addChild: left node and right node are assigned");
}

ExpressionTree::iterator ExpressionTree::addLeftChild(const std::string val, iterator node)
{
    if(node.ptr->left == nullptr)
    {
        node.ptr->left = new Node;
        node.ptr->left->value = val;
        node.ptr->left->parent = node.ptr;
        node.ptr->left->left = nullptr;
        node.ptr->left->right = nullptr;
        return iterator(node.ptr->left);
    }
    else
        throw std::out_of_range("ExpressionTree::addLeftChild: left node is assigned");
}

ExpressionTree::iterator ExpressionTree::addRightChild(const std::string val, iterator node)
{
    if(node.ptr->right == nullptr)
    {
        node.ptr->right = new Node;
        node.ptr->right->value = val;
        node.ptr->right->parent = node.ptr;
        node.ptr->right->left = nullptr;
        node.ptr->right->right = nullptr;
        return iterator(node.ptr->right);
    }
    else
        throw std::out_of_range("ExpressionTree::addRightChild: right node is assigned");
}


void ExpressionTree::eraseNode(iterator node)
{
    if(node.ptr != root)
    {
        if(node.ptr->parent != nullptr)
        {
            if(node.ptr->parent->left == node.ptr)
                node.ptr->parent->left = nullptr;
            else if(node.ptr->parent->right == node.ptr)
                node.ptr->parent->right = nullptr;
        }
        destroyNode(node.ptr);
    }
    else
    {
        destroyNode(node.ptr);
        root = nullptr;
    }
}


std::string& ExpressionTree::getRootValue()
{
    if(root != nullptr)
        return root->value;
}
std::string& ExpressionTree::getNodeValue(iterator node)
{
    return node.ptr->value;
}
std::string& ExpressionTree::getChildValue(iterator node, std::size_t index)
{
    if(index == 0)
        return node.ptr->left->value;
    else if(index == 1)
        return node.ptr->right->value;
    else
        throw std::out_of_range("ExpressionTree::getChildValue: index > 1");
}



bool ExpressionTree::empty()
{
    return (root == nullptr);
}

void ExpressionTree::clear()
{
    destroyNode(root);
    root = nullptr;
}



void ExpressionTree::copyChildren(Node* destination_parent, Node* source_parent)
{
    if(source_parent->left != nullptr)
        copyChildren(addLeftChild(source_parent->left->value, destination_parent).ptr, source_parent->left);
    if(source_parent->right != nullptr)
        copyChildren(addRightChild(source_parent->right->value, destination_parent).ptr, source_parent->right);
}

void ExpressionTree::destroyNode(Node* node)
{
    if(node != nullptr)
    {
        if(node->left != nullptr)
            destroyNode(node->left);
        if(node->right != nullptr)
            destroyNode(node->right);
        delete node;
    }
}
ExpressionTree::Node* ExpressionTree::createNode(const std::string val)
{
    Node* node = new Node;
    node->value = val;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
}



void ExpressionTree::printTree(){
    innerPrintTree(root);
}
void ExpressionTree::innerPrintTree(Node* node, std::string str, std::string str2)
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

