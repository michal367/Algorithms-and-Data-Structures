#pragma once

#include <iterator>
#include <stdexcept>
#include <map>

class HuffmanCoding
{
    struct Node
    {
        char key;
        unsigned int count;
        Node* left;
        Node* right;
        Node* next;
    };
    Node* root;

    std::string data;
    std::map<char, std::string> letters;
    std::string code;

public:
    HuffmanCoding();
    HuffmanCoding(const HuffmanCoding& other);
    HuffmanCoding operator=(const HuffmanCoding& other);
    ~HuffmanCoding();

    std::string encode(std::string data);
    std::string decode();

    std::string getData();
    std::string getCode();
    std::map<char, std::string> getLetters();

    bool empty();
    void clear();

    //
    void PRINT();
    void print(Node* node, std::string str="", std::string str2="");
    //

private:
    void copyChildren(Node* destination_parent, Node* source_parent);
    void destroyNode(Node* node);
    Node* createNode(const char key, unsigned int count);
    Node* addLeftChild(const char key, Node* node);
    Node* addRightChild(const char key, Node* node);
    std::string deleteDuplicates(std::string str);
    void makeLetters(Node* node, std::string code);
};


HuffmanCoding::HuffmanCoding()
{
    root = nullptr;
}
HuffmanCoding::HuffmanCoding(const HuffmanCoding& other)
{
    root = nullptr;
    if(other.root != nullptr)
    {
        root = createNode(other.root->key, other.root->count);
        copyChildren(root, other.root);
    }
    data = other.data;
    letters = other.letters;
    code = other.code;
}
HuffmanCoding HuffmanCoding::operator=(const HuffmanCoding& other)
{
    if(this != &other)
    {
        if(root != nullptr)
        {
            destroyNode(root);
            root = nullptr;
        }
        if(other.root != nullptr)
        {
            root = createNode(other.root->key, other.root->count);
            copyChildren(root, other.root);
        }
    }
    data = other.data;
    letters = other.letters;
    code = other.code;
    return *this;
}

HuffmanCoding::~HuffmanCoding()
{
    destroyNode(root);
}



std::string HuffmanCoding::encode(std::string data)
{
    if(data != "")
    {
        if(root != nullptr)
        {
            destroyNode(root);
            root = nullptr;
        }
        this->data = data;
        letters.clear();
        code = "";

        // ==========
        root = createNode(data.front(), 1);
        for(auto it = data.begin()+1; it != data.end(); ++it)
        {
            Node* temp = root;
            Node* temp_prev = nullptr;
            while(temp != nullptr && temp->key != *it)
            {
                temp_prev = temp;
                temp = temp->next;
            }
            if(temp == nullptr)
            {
                Node* t = root;
                root = createNode(*it, 1);
                root->next = t;
            }
            else
            {
                temp->count++;
                Node* temp2 = temp;
                while(temp2->next != nullptr && temp2->next->count < temp->count)
                    temp2 = temp2->next;
                if(temp2 != temp)
                {
                    if(temp != root)
                        temp_prev->next = temp->next;
                    else
                        root = temp->next;
                    temp->next = temp2->next;
                    temp2->next = temp;
                }
            }


        }
        /*for(Node* it = root; it != nullptr; it=it->next)
            std::cout << it->key << ": " << it->count << std::endl;
        std::cout << "---" << std::endl;*/

        // ==========
        while(root->next != nullptr)
        {
            Node* parent = createNode('\0', root->count + root->next->count);
            parent->left = root;
            parent->right = root->next;

            if(root->next->next != nullptr)
            {
                root = root->next->next;
                Node* it = root;
                if(it->count >= parent->count)
                {
                    parent->next = it;
                    root = parent;
                }
                else
                {
                    while(it->next != nullptr && it->next->count < parent->count)
                        it = it->next;
                    parent->next = it->next;
                    it->next = parent;
                }
            }
            else
                root = parent;
        }

        // ==========
        makeLetters(root, "");

        // ==========

        for(auto it = data.begin(); it != data.end(); ++it)
            code += letters[*it];

        return code;
    }
}


std::string HuffmanCoding::decode()
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


std::string HuffmanCoding::getData()
{
    return data;
}
std::string HuffmanCoding::getCode()
{
    return code;
}
std::map<char, std::string> HuffmanCoding::getLetters()
{
    return letters;
}


bool HuffmanCoding::empty()
{
    return (root == nullptr);
}
void HuffmanCoding::clear()
{
    destroyNode(root);
    root = nullptr;
}


HuffmanCoding::Node* HuffmanCoding::addLeftChild(const char key, Node* node)
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
        throw std::out_of_range("HuffmanCoding::addLeftChild: left node is assigned");
}
HuffmanCoding::Node* HuffmanCoding::addRightChild(const char key, Node* node)
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
        throw std::out_of_range("HuffmanCoding::addRightChild: right node is assigned");
}

void HuffmanCoding::copyChildren(Node* destination_parent, Node* source_parent)
{
    if(source_parent->left != nullptr)
        copyChildren(addLeftChild(source_parent->left->key, destination_parent), source_parent->left);
    if(source_parent->right != nullptr)
        copyChildren(addRightChild(source_parent->right->key, destination_parent), source_parent->right);
}

void HuffmanCoding::destroyNode(Node* node)
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
HuffmanCoding::Node* HuffmanCoding::createNode(const char key, unsigned int count)
{
    Node* node = new Node;
    node->key = key;
    node->count = count;
    node->left = nullptr;
    node->right = nullptr;
    node->next = nullptr;
    return node;
}
std::string HuffmanCoding::deleteDuplicates(std::string str)
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

void HuffmanCoding::makeLetters(Node* node, std::string code)
{
    if(node != nullptr)
    {
        makeLetters(node->left, code+'0');
        makeLetters(node->right, code+'1');
        if(node->left == nullptr && node->right == nullptr)
            letters.insert(std::pair<char, std::string>(node->key, code));
    }
}



//=============


#include <iostream>
void HuffmanCoding::PRINT()
{
    print(root);
    std::cout << std::endl;
    for(auto it = letters.begin(); it != letters.end(); ++it)
        std::cout << it->first << " " << it->second << "\n";
    std::cout << std::endl << data << std::endl;
    std::cout << code << std::endl;
}
void HuffmanCoding::print(Node* it, std::string str/*=""*/, std::string str2/*=""*/)
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


