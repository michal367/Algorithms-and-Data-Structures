#ifndef STRING_NEW_METHODS_H
#define STRING_NEW_METHODS_H

#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

class String : public std::string
{
public:
    String() : std::string() {}
    String(const char* s) : std::string(s) {}
    String(const std::string& str) : std::string(str) {}
    String(const String& s) : std::string(s) {}
    String(std::size_t n, char c) : std::string(n,c) {}
    String(const char* s, std::size_t n) : std::string(s,n) {}
    String(const String& str, std::size_t pos, std::size_t len = npos) : std::string(str, pos, len) {}
    template <class InputIterator>
    String(InputIterator first, InputIterator last) : std::string(first, last) {}
    ~String() {}

    operator std::string()
    {
        return( * this );
    }

    String substring(std::size_t pos1, std::size_t pos2) const;

    std::vector<String> split_longd(const String& delimiters) const;
    std::vector<String> split_shortd(const String& delimiters) const;

    void toUpperCase();
    void toLowerCase();

    void left_trim();
    void right_trim();
    void trim();

    bool startsWith(const String& prefix);
    bool endsWith(const String& suffix);

    bool hasPunct();
    std::size_t countChar(const char character);
    std::size_t countDigits();
    bool isAllPrintable();
    void replaceAll(const char character, const char character_instead);
    void whitespacesToSpace();
    bool hasTheSameCharacters();

    std::size_t positionOfMismatch(const String& b);
    void insertAfterEveryLetterInString(const String& letters);
    void sortLetters();
};

String String::substring(std::size_t pos1, std::size_t pos2) const
{
    if(pos2 >= pos1)
        return String(substr(pos1, pos2-pos1+1));
}

std::vector<String> String::split_longd(const String& delimiters) const
{
    std::vector<String> v;
    std::size_t pos = 0;
    std::size_t pos2 = 0;
    while(find(delimiters, pos) != std::string::npos)
    {
        pos2 = find_first_of(delimiters, pos);
        if(pos2 != pos)
            v.push_back(substring(pos, pos2-1));
        pos = pos2+1;
    }
    v.push_back(substring(pos,size()-1));
    return v;
}
std::vector<String> String::split_shortd(const String& delimiters) const
{
    std::vector<String> v;
    std::size_t pos = 0;
    std::size_t pos2 = 0;
    while(find_first_of(delimiters, pos) != std::string::npos)
    {
        pos2 = find_first_of(delimiters, pos);
        if(pos2 != pos)
            v.push_back(substring(pos, pos2-1));
        pos = pos2+1;
    }
    v.push_back(substring(pos,size()-1));
    return v;
}


void String::toUpperCase()
{
    std::transform(begin(), end(), begin(), std::ptr_fun<int, int>(toupper));
}
void String::toLowerCase()
{
    std::transform(begin(), end(), begin(), std::ptr_fun<int, int>(tolower));
}


void String::left_trim()
{
    erase(0,find_first_not_of(" "));
}
void String::right_trim()
{
    erase(find_last_not_of(" ")+1);
}
void String::trim()
{
    left_trim();
    right_trim();
}

bool String::startsWith(const String& prefix)
{
    return find(std::string(prefix)) == 0;
}
bool String::endsWith(const String& suffix)
{
    return rfind(std::string(suffix)) == (size()-suffix.size());
}


bool String::hasPunct()
{
    return std::find_if(begin(), end(), std::ptr_fun<int,int>(ispunct)) != end();
}
std::size_t String::countChar(const char character)
{
    return std::count(begin(), end(), character);
}
std::size_t String::countDigits()
{
    return std::count_if(begin(), end(), std::ptr_fun<int, int>(isdigit));
}
bool String::isAllPrintable()
{
    return std::count_if(begin(), end(), not1(std::ptr_fun<int, int>(isspace))) == size();
}
void String::replaceAll(const char character, const char character_instead)
{
    std::replace(begin(), end(), character, character_instead);
}
void String::whitespacesToSpace()
{
    std::replace_if(begin(), end(), std::ptr_fun<int,int>(isspace), ' ');
}
bool String::hasTheSameCharacters()
{
    return std::count(begin(), end(), at(0)) == size();
}

std::size_t String::positionOfMismatch(const String& b)
{
    if(size() == b.size())
        return std::mismatch(begin(), end(), b.begin()).first - begin();
}
void String::insertAfterEveryLetterInString(const String& letters)
{
    for(std::size_t pos = 1; pos<=size(); pos += letters.size()+1)
        insert(pos, letters);
}

bool min_char(char a, char b)
{
    return a<b;
}

void String::sortLetters()
{
    std::sort(begin(), end(), min_char);
}



#endif // STRING_NEW_METHODS_H
