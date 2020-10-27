#pragma once

#include <iterator>
#include <stdexcept>
#include <map>


class Coding
{
    struct Node
    {
        char key;
        Node* left;
        Node* right;
    };
    Node* root;

    std::string data;
    std::map<char, std::string> letters;
    std::string code;

public:
    Coding();
    Coding(const Coding& other);
    Coding operator=(const Coding& other);
    ~Coding();

    void createRoot();

    std::string encode(std::string data);
    std::string encode(std::map<char, std::string>& letters, std::string data);
    std::string decode();


    bool empty();
    void clear();

    //
    void PRINT();
    void print(Node* node, std::string str="", std::string str2="");
    //

private:
    void copyChildren(Node* destination_parent, Node* source_parent);
    void destroyNode(Node* node);
    Node* createNode(const char key);
    Node* addLeftChild(const char key, Node* node);
    Node* addRightChild(const char key, Node* node);
    std::string deleteDuplicates(std::string str);
};


Coding::Coding()
{
    root = nullptr;
}
Coding::Coding(const Coding& other)
{
    root = nullptr;
    if(other.root != nullptr)
    {
        createRoot();
        copyChildren(root, other.root);
    }
    data = other.data;
    letters = other.letters;
    code = other.code;
}
Coding Coding::operator=(const Coding& other)
{
    if(this != &other)
    {
        root = nullptr;
        if(other.root != nullptr)
        {
            createRoot();
            copyChildren(root, other.root);
        }
    }
    return *this;
    data = other.data;
    letters = other.letters;
    code = other.code;
}

Coding::~Coding()
{
    destroyNode(root);
}



std::string Coding::encode(std::string data)
{
    if(root != nullptr)
    {
        destroyNode(root);
        root = nullptr;
    }
    this->data = data;
    letters.clear();
    code = "";

    createRoot();

    std::string data2 = deleteDuplicates(data);

    for(auto it = data2.cbegin(); it != data2.cend()-1; ++it)
    {
        std::string letter_code = "";
        Node* temp = root;
        while(temp->left != nullptr)
        {
            letter_code += "1";
            if(temp->right == nullptr)
                temp = addRightChild('\0', temp);
            else
                temp = temp->right;
        }
        letter_code += "0";
        letters.insert(std::pair<char, std::string>(*it, letter_code));
        addLeftChild(*it, temp);
    }

    std::string letter_code = "";
    Node* temp = root;
    while(temp->right != nullptr)
    {
        temp = temp->right;
        letter_code += "1";
    }
    letter_code += "1";
    letters.insert(std::pair<char, std::string>(data2.back(), letter_code));
    addRightChild(data2.back(), temp);


    for(auto it = data.begin(); it != data.end(); ++it)
        code += letters[*it];
    return code;
}
std::string Coding::encode(std::map<char, std::string>& letters, std::string data)
{
    if(root != nullptr)
    {
        destroyNode(root);
        root = nullptr;
    }
    this->data = data;
    this->letters = letters;
    code = "";

    createRoot();
    for(auto it = letters.begin(); it != letters.end(); ++it)
    {
        Node* temp = root;
        for(auto it2 = it->second.begin(); it2 != it->second.end()-1; ++it2)
        {
            if(*it2 == '0')
            {
                if(temp->left == nullptr)
                    temp = addLeftChild('\0', temp);
                else
                    temp = temp->left;
            }
            else if(*it2 == '1')
            {
                if(temp->right == nullptr)
                    temp = addRightChild('\0', temp);
                else
                    temp = temp->right;
            }
        }
        if(it->second.back() == '0')
            addLeftChild(it->first, temp);
        else if(it->second.back() == '1')
            addRightChild(it->first, temp);
    }
    for(auto it = data.begin(); it != data.end(); ++it)
        code += letters[*it];
    return code;
}

std::string Coding::decode()
{
    std::string result = "";
    Node* temp = root;
    for(auto it = code.begin(); it != code.end(); ++it)
    {
        if(*it == '0')
            temp = temp->left;
        else if(*it == '1')
            temp = temp->right;
        if(temp->key != '\0')
        {
            result += temp->key;
            temp = root;
        }
    }
    return result;
}


bool Coding::empty()
{
    return (root == nullptr);
}
void Coding::clear()
{
    destroyNode(root);
    root = nullptr;
}

void Coding::createRoot()
{
    root = new Node;
    root->key = '\0';
    root->left = nullptr;
    root->right = nullptr;
}


Coding::Node* Coding::addLeftChild(const char key, Node* node)
{
    if(node->left == nullptr)
    {
        node->left = new Node;
        node->left->key = key;
        node->left->left = nullptr;
        node->left->right = nullptr;
        return node->left;
    }
    else
        throw std::out_of_range("Coding::addLeftChild: left node is assigned");
}
Coding::Node* Coding::addRightChild(const char key, Node* node)
{
    if(node->right == nullptr)
    {
        node->right = new Node;
        node->right->key = key;
        node->right->left = nullptr;
        node->right->right = nullptr;
        return node->right;
    }
    else
        throw std::out_of_range("Coding::addRightChild: right node is assigned");
}

void Coding::copyChildren(Node* destination_parent, Node* source_parent)
{
    if(source_parent->left != nullptr)
        copyChildren(addLeftChild(source_parent->left->key, destination_parent), source_parent->left);
    if(source_parent->right != nullptr)
        copyChildren(addRightChild(source_parent->right->key, destination_parent), source_parent->right);
}

void Coding::destroyNode(Node* node)
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
Coding::Node* Coding::createNode(const char key)
{
    Node* node = new Node;
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}
std::string Coding::deleteDuplicates(std::string str)
{
    for(std::string::iterator it = str.begin(); it != str.end(); ++it)
    {
        for(std::string::iterator it2 = it+1; it2 != str.end();)
        {
            if(*it == *it2)
                str.erase(it2);
            else
                ++it2;
        }
    }
    return str;
}





//=============


#include <iostream>
void Coding::PRINT()
{
    print(root);
    std::cout << std::endl;
    for(auto it = letters.begin(); it != letters.end(); ++it)
        std::cout << it->first << " " << it->second << "\n";
    std::cout << std::endl << data << std::endl;
    std::cout << code << std::endl;
}
void Coding::print(Node* it, std::string str/*=""*/, std::string str2/*=""*/)
{
    if(it != nullptr)
    {
        if(str2 == "")
        {
            print(it->right, str, "\xda\xc4");
            std::cout << str << str2 << it->key << std::endl;
            print(it->left, str, "\xc0\xc4");
        }
        else
        {
            if(str2 == "\xc0\xc4")
            {
                print(it->right, str+"\xb3 ", "\xda\xc4");
                std::cout << str << str2 << it->key << std::endl;
                print(it->left, str+"  ", "\xc0\xc4");
            }
            else
            {
                print(it->right, str+"  ", "\xda\xc4");
                std::cout << str << str2 << it->key << std::endl;
                print(it->left, str+"\xb3 ", "\xc0\xc4");
            }
        }
    }
}


