#include <iostream>
#include <cstdlib>
#include <sstream>
#include <queue>
#include <cctype>
#include "AVLTree.h"

using namespace std;

bool isNumber(string& str)
{
    for(int i=0; i<str.size(); ++i)
    {
        if(!isdigit(str.at(i)))
            return 0;
    }
    return 1;
}
int strToInt(string& str)
{
    int result;
    stringstream ss;
    ss << str;
    ss >> result;
    return result;
}



int main()
{
    AVLTree<int> avl;

    while(1)
    {
        system("cls");
        cout << "What do you want to do?" << endl
             << "1. Add node to AVL" << endl
             << "2. Remove node from AVL" << endl
             << "3. Find number in AVL" << endl
             << "4. Print AVL" << endl
             << "5. Exit" << endl;
        char z;
        do{
            cin >> z;
        }while(z != '1' && z != '2' && z != '3' && z != '4' && z != '5');

        if(z == '1')
        {
            system("cls");
            if(!avl.empty()){
                avl.printTree();
                cout << endl;
            }
            cout << "Type numbers to add:" << endl
                 << "(e - exit)" << endl;
            while(1)
            {
                string str;
                int liczba;
                do{
                    cin >> str;
                }while(!isNumber(str) && str != "e" && str != "exit");
                if(str == "e" || str == "exit")
                    break;

                liczba = strToInt(str);
                avl.add(liczba);

                cout << endl;
                avl.printTree();
                cout << endl;
            }
        }
        else if(z == '2')
        {
            system("cls");
            if(!avl.empty()){
                avl.printTree();
                cout << endl;
            }
            cout << "Type numbers to remove:" << endl
                 << "(e - exit)" << endl;
            while(1)
            {
                string str;
                int liczba;
                do{
                    cin >> str;
                }while(!isNumber(str) && str != "e" && str != "exit");
                if(str == "e" || str == "exit")
                    break;

                liczba = strToInt(str);

                AVLTree<int>::iterator it = avl.find(liczba);
                if(it != NULL)
                    avl.remove(it);
                else
                    cout << "There is no such number in the tree" << endl;

                cout << endl;
                avl.printTree();
                cout << endl;
            }
        }
        else if(z == '3')
        {
            system("cls");
            if(!avl.empty()){
                avl.printTree();
                cout << endl;
            }
            cout << "Type numbers to find:" << endl
                 << "(e - exit)" << endl;
            while(1)
            {
                string str;
                int liczba;
                do{
                    cin >> str;
                }while(!isNumber(str) && str != "e" && str != "exit");
                if(str == "e" || str == "exit")
                    break;

                liczba = strToInt(str);

                AVLTree<int>::iterator it = avl.find(liczba);
                if(it != NULL)
                    cout << "Found" << endl;
                else
                    cout << "Not found" << endl;

                cout << endl;
                avl.printTree();
                cout << endl;
            }
        }
        else if(z == '4')
        {
            system("cls");
            avl.printTree();
            cout << endl;
            system("pause");
        }
        else if(z == '5')
        {
            return 0;
        }
    }


    system("pause");
    return 0;
}
