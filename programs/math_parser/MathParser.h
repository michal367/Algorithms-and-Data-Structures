#ifndef MATHPARSER_H
#define MATHPARSER_H

#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <cmath>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#ifndef M_E
    #define M_E 2.71828182845904523536
#endif


class MathParser
{
public:
    static std::string toRPN(const std::string& expr);
    static double calculateRPN(const std::string& RPNexpr);

    static double calculateExpr(const std::string& expr);

private:
    static bool is_space_string(const std::string& str);
    static bool is_number(const std::string& str);
    static bool is_constant_number(const std::string& str);
    static bool is_operator(const std::string& str);
    static bool is_opening_parenthesis(const std::string& str);
    static bool is_closing_parenthesis(const std::string& str);

    static int priority_of_operator(const std::string& str);

    static double str_to_number(const std::string& str);

    static std::vector<std::string> split(const std::string& str, const std::string& delimiters);
    static std::vector<std::string> split_with_delimiters(const std::string& str, const std::string& delimiters);
    static void trim(std::string& str);
    static std::string to_lower_case(const std::string& str);
};



#endif // MATHPARSER_H
