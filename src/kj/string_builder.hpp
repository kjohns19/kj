#ifndef INCLUDED_STRING_BUILDER
#define INCLUDED_STRING_BUILDER

#include <sstream>

namespace kj {

class StringBuilder
{
public:
    template<typename T>
    StringBuilder& operator<<(T&& value);
    StringBuilder& operator<<(std::ostream& (*func)(std::ostream&));
    StringBuilder& operator<<(std::basic_ios<char>& (*func)(std::basic_ios<char>&));
    StringBuilder& operator<<(std::ios_base& (*func)(std::ios_base&));
    operator std::string() const { return d_stream.str(); }
private:
    std::ostringstream d_stream;
};

template<typename T>
StringBuilder& StringBuilder::operator<<(T&& value)
{
    d_stream << std::forward<T>(value);
    return *this;
}
inline StringBuilder& StringBuilder::operator<<(
        std::ostream& (*func)(std::ostream&))
{
    d_stream << func;
    return *this;
}
inline StringBuilder& StringBuilder::operator<<(
        std::basic_ios<char>& (*func)(std::basic_ios<char>&))
{
    d_stream << func;
    return *this;
}
inline StringBuilder& StringBuilder::operator<<(
        std::ios_base& (*func)(std::ios_base&))
{
    d_stream << func;
    return *this;
}

} // close namespace kj

#endif //INCLUDED_STRING_BUILDER
