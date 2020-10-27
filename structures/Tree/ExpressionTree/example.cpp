#include <iostream>
#include <cstdlib>
#include "ExpressionTree.h"

using namespace std;

void printPostorder(ExpressionTree::iterator it)
{
    if(it != nullptr)
    {
        printPostorder(it.leftChild());
        printPostorder(it.rightChild());
        cout << *it << ' ';
    }
}


int main()
{
    cout << "Expression Tree" << endl << endl;
    string exprs[] = {"2+3", "2+3*7", "sin(ln(pi))", "e*pi", "(10 * 2 / 3) ^ (1 - 0)", "(a + b ^ (c - d)) / he * f ^ g","-8", "x*(2+2*x^5/(x^4))*x/2"};
    size_t expr_size = 8;

    for(int i=0; i<expr_size; ++i)
    {
        cout << "====================" << endl;
        cout << "expression: " << exprs[i] << endl;
        ExpressionTree et(exprs[i]);

        cout << "RPN: ";
        printPostorder(et.begin());

        cout << endl << endl;
        et.printTree();
        cout << endl << endl;
    }

    cout << endl;
    return 0;
}
