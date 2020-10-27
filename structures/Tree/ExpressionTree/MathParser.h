#ifndef MATHPARSER_H
#define MATHPARSER_H

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#ifndef M_E
    #define M_E 2.71828182845904523536
#endif

#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <cmath>
#include <iostream>

class MathParser
{
public:
    static std::string toRPN(const std::string& expr);
    static double calculateRPN(const std::string& RPNexpr);

    static double calculateExpr(const std::string& expr);

    static bool is_space_string(const std::string& str);
    static bool is_number(const std::string& str);
    static bool is_constant_number(const std::string& str);
    static bool is_operator(const std::string& str);
    static bool is_binary_operator(const std::string& str);
    static bool is_unary_operator(const std::string& str);
    static bool is_opening_parenthesis(const std::string& str);
    static bool is_closing_parenthesis(const std::string& str);

    static int priority_of_operator(const std::string& str);

    static double str_to_number(const std::string& str);

    static std::vector<std::string> split(const std::string& str, const std::string& delimiters);
    static std::vector<std::string> split_with_delimiters(const std::string& str, const std::string& delimiters);
    static void trim(std::string& str);
    static std::string to_lower_case(const std::string& str);
};




std::string MathParser::toRPN(const std::string& expr)
{
    std::vector<std::string> exprs = split_with_delimiters(expr, "+-*/^()");

    std::string result;
    std::stack<std::string> expr_stack;

    for(std::vector<std::string>::iterator it = exprs.begin(); it != exprs.end(); ++it)
    {
        trim(*it);
        *it = to_lower_case(*it);

        if(is_number(*it) || is_constant_number(*it))
        {
            result += *it + ' ';
        }
        else if(is_operator(*it))
        {
            if((*it == "-" || *it == "+") && (it == exprs.begin() || *(it-1) == "("))
                result += "0 ";
            while(!expr_stack.empty() && priority_of_operator(expr_stack.top()) >= priority_of_operator(*it))
            {
                result += expr_stack.top() + ' ';
                expr_stack.pop();
            }
            expr_stack.push(*it);
        }
        else if(is_opening_parenthesis(*it))
        {
            expr_stack.push(*it);
        }
        else if(is_closing_parenthesis(*it))
        {
            while(!is_opening_parenthesis(expr_stack.top()))
            {
                result += expr_stack.top() + ' ';
                expr_stack.pop();
            }
            expr_stack.pop();
        }
        else
        {
            result += *it + ' ';
            //std::cout << "Error: unknown expression \"" << *it << "\"" << std::endl;
        }
    }

    while(!expr_stack.empty())
    {
        if(expr_stack.top() == "(")
        {
            std::cout << "Error: missing \")\"" << std::endl;
            return "";
        }
        result += expr_stack.top() + ' ';
        expr_stack.pop();
    }

    if(!result.empty())
        result.erase(result.size()-1);

    return result;
}
double MathParser::calculateRPN(const std::string& RPNexpr)
{
    std::vector<std::string> exprs = split(RPNexpr, " ");

    std::stack<double> numbers_stack;

    for(std::vector<std::string>::iterator it = exprs.begin(); it != exprs.end(); ++it)
    {
        if(is_number(*it))
        {
            numbers_stack.push(str_to_number(*it));
        }
        else if(is_constant_number(*it))
        {
            if(*it == "pi")
                numbers_stack.push(M_PI);
            else if(*it == "e")
                numbers_stack.push(M_E);
        }
        else if(is_operator(*it))
        {
            double a = numbers_stack.top();
            numbers_stack.pop();
            double c;
            if(*it == "+")
            {
                double b = numbers_stack.top();
                numbers_stack.pop();
                c = b+a;
            }
            else if(*it == "-")
            {
                double b = numbers_stack.top();
                numbers_stack.pop();
                c = b-a;
            }
            else if(*it == "*")
            {
                double b = numbers_stack.top();
                numbers_stack.pop();
                c = b*a;
            }
            else if(*it == "/")
            {
                double b = numbers_stack.top();
                numbers_stack.pop();
                c = b/a;
            }
            else if(*it == "^")
            {
                double b = numbers_stack.top();
                numbers_stack.pop();
                c = pow(b,a);
            }
            else if(*it == "abs")
                c = abs(a);
            else if(*it == "sqrt")
                c = sqrt(a);
            else if(*it == "log")
                c = log10(a);
            else if(*it == "ln")
                c = log(a);
            else if(*it == "sin")
                c = sin(a);
            else if(*it == "cos")
                c = cos(a);
            else if(*it == "tan")
                c = tan(a);
            else if(*it == "ctan")
                c = (cos(a)/sin(a));
            numbers_stack.push(c);
        }
        else
        {
            //std::cout << "Error: unknown expression \"" << *it << "\"" << std::endl;
            return 0;
        }
    }

    return numbers_stack.top();
}

double MathParser::calculateExpr(const std::string& expr)
{
    return calculateRPN(toRPN(expr));
}



bool MathParser::is_number(const std::string& str)
{
    if(str.size() > 0)
    {
        size_t count_digit=0;
        bool is_include_dot=0;
        for(std::string::const_iterator it = str.begin(); it != str.end(); ++it)
        {
            if(isdigit(*it))
                ++count_digit;
            else if(!is_include_dot && *it == '.')
                is_include_dot = 1;
            else if(is_include_dot && *it == '.')
                return 0;
            else
                return 0;
        }

        return (count_digit == str.size()) || (count_digit == str.size()-1 && is_include_dot);
    }
    else
        return 0;
}
bool MathParser::is_constant_number(const std::string& str)
{
    if(str == "e" || str == "pi")
        return 1;
    else
        return 0;
}
bool MathParser::is_operator(const std::string& str)
{
    if(str == "+" || str == "-" || str == "*" || str == "/" || str == "^" ||
       str == "abs" || str == "sqrt" || str == "log" || str == "ln" ||
       str == "sin" || str == "cos" || str == "tan" || str == "ctan")
        return 1;
    else
        return 0;
}
bool MathParser::is_binary_operator(const std::string& str)
{
    if(str == "+" || str == "-" || str == "*" || str == "/" || str == "^")
        return true;
    else
        return false;
}
bool MathParser::is_unary_operator(const std::string& str)
{
    if(str == "abs" || str == "sqrt" || str == "log" || str == "ln" ||
       str == "sin" || str == "cos" || str == "tan" || str == "cot")
        return true;
    else
        return false;
}
bool MathParser::is_opening_parenthesis(const std::string& str)
{
    if(str == "(")
        return 1;
    else
        return 0;
}
bool MathParser::is_closing_parenthesis(const std::string& str)
{
    if(str == ")")
        return 1;
    else
        return 0;
}

int MathParser::priority_of_operator(const std::string& str)
{
    if(str == "(")
        return 0;
    else if(str == "+" || str == "-" || str == ")")
        return 1;
    else if(str == "*" || str == "/")
        return 2;
    else if(str == "^" || str == "sqrt")
        return 3;
    else if(str == "abs" || str == "log" || str == "ln" ||
            str == "sin" || str == "cos" || str == "tan" || str == "ctan")
        return 4;
    return -1;
}

double MathParser::str_to_number(const std::string& str)
{
    double result;
    std::stringstream ss;
    ss << str;
    ss >> result;
    return result;
}



bool MathParser::is_space_string(const std::string& str)
{
    size_t count_space=0;
    for(std::string::const_iterator it = str.begin(); it != str.end(); ++it)
        if(isspace(*it))
            ++count_space;

    return count_space == str.size();
}

std::vector<std::string> MathParser::split(const std::string& str, const std::string& delimiters)
{
    std::vector<std::string> res;
    size_t pos=0, pos2=0;
    while(str.find_first_of(delimiters, pos) != std::string::npos)
    {
        pos2 = str.find_first_of(delimiters, pos);
        res.push_back(str.substr(pos, pos2-pos));
        pos = pos2+1;
    }
    res.push_back(str.substr(pos));
    return res;
}

std::vector<std::string> MathParser::split_with_delimiters(const std::string& str, const std::string& delimiters)
{
    std::vector<std::string> res;
    size_t pos = 0, pos2 = 0;
    while(str.find_first_of(delimiters, pos) != std::string::npos)
    {
        pos2 = str.find_first_of(delimiters, pos);
        if(pos != pos2 && !is_space_string(str.substr(pos, pos2-pos)))
            res.push_back(str.substr(pos, pos2-pos));
        res.push_back(str.substr(pos2, 1));
        pos = pos2+1;
    }
    if(pos != str.size() && !is_space_string(str.substr(pos)))
        res.push_back(str.substr(pos));

    return res;
}

 void MathParser::trim(std::string& str)
{
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ')+1);
}
std::string MathParser::to_lower_case(const std::string& str)
{
    std::string result = str;
    for(std::string::iterator it = result.begin(); it != result.end(); ++it)
        *it = tolower(*it);
    return result;
}


#endif // MATHPARSER_H
