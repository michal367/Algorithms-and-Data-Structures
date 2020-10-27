#include <iostream>
#include "MathParser.h"

using namespace std;

int main()
{
    cout << "Math Parser" << endl << "Type expression to calculate" << endl << endl;

    string expr;

    do{
        getline(cin,expr);
        if(expr != "exit" && expr != "quit")
        {
            cout << "result: " << MathParser::calculateExpr(expr) << endl;
            cout << endl;
        }
    }while(expr != "exit" && expr != "quit");

    return 0;
}
