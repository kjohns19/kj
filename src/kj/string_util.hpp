#ifndef INCLUDED_KJ_STRING_UTIL
#define INCLUDED_KJ_STRING_UTIL

#include <string>

namespace kj {
namespace StringUtil {

std::string& upcase   (std::string* str);
std::string  upcased  (std::string  str);
std::string& downcase (std::string* str);
std::string  downcased(std::string  str);

int caseCompare(std::string s1, std::string s2);
bool caseEqual(const std::string& s1, const std::string& s2);
bool caseLess(const std::string& s1, const std::string& s2);

std::string& ltrim   (std::string* str);
std::string  ltrimmed(std::string  str);
std::string& rtrim   (std::string* str);
std::string  rtrimmed(std::string  str);
std::string& trim    (std::string* str);
std::string  trimmed (std::string  str);

std::string& replace (const std::string& from, const std::string& to, std::string* str);
std::string  replaced(const std::string& from, const std::string& to, std::string  str);
std::string& replaceAll (const std::string& from, const std::string& to, std::string* str);
std::string  replacedAll(const std::string& from, const std::string& to, std::string  str);

} // close namespace StringUtil
} // close namespace kj

#endif //INCLUDED_KJ_STRING_UTIL
