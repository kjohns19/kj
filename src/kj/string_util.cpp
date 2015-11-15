#include <kj/string_util.hpp>
#include <algorithm>
#include <cctype>

namespace kj {
namespace StringUtil {

std::string& upcase(std::string* str)
{
    std::transform(
        str->begin(), str->end(),
        str->begin(),
        [](char c) { return std::toupper(c); });
    return *str;
}
std::string upcased(std::string str)
{
    return upcase(&str);
}

std::string& downcase(std::string* str)
{
    std::transform(
        str->begin(), str->end(),
        str->begin(),
        [](char c) { return std::tolower(c); });
    return *str;
}
std::string downcased(std::string str)
{
    return downcase(&str);
}

int caseCompare(std::string s1, std::string s2)
{
    return upcase(&s1).compare(upcase(&s2));
}
bool caseLess(const std::string& s1, const std::string& s2)
{
    return caseCompare(s1, s2) < 0;
}
bool caseEqual(const std::string& s1, const std::string& s2)
{
    return caseCompare(s1, s2) == 0;
}

std::string& ltrim(std::string* str)
{
    str->erase(
        str->begin(),
        std::find_if(
            str->begin(), str->end(),
            [](char c) { return !std::isspace(c); }));
    return *str;
}
std::string ltrimmed(std::string str)
{
    return ltrim(&str);
}

std::string& rtrim(std::string* str)
{
    str->erase(
        std::find_if(
            str->rbegin(), str->rend(),
            [](char c) { return !std::isspace(c); }).base(),
        str->end());
    return *str;
}
std::string rtrimmed(std::string str)
{
    return rtrim(&str);
}

std::string& trim(std::string* str)
{
    return rtrim(&ltrim(str));
}
std::string trimmed(std::string str)
{
    return trim(&str);
}


std::string& replace(const std::string& from, const std::string& to, std::string* str)
{
    std::string::size_type search = str->find(from);
    if (search != std::string::npos)
        str->replace(search, from.length(), to);
    return *str;
}
std::string replaced(const std::string& from, const std::string& to, std::string str)
{
    return replace(from, to, &str);
}

std::string& replaceAll(const std::string& from, const std::string& to, std::string* str)
{
    std::string::size_type startPos = str->size();
    std::string::size_type search;
    while((search = str->rfind(from, startPos)) != std::string::npos)
    {
        str->replace(search, from.length(), to);
        startPos = search;
    }
    return *str;
}
std::string replacedAll(const std::string& from, const std::string& to, std::string str)
{
    return replaceAll(from, to, &str);
}

} // close namespace StringUtil
} // close namespace kj

