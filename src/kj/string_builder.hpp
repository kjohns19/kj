#ifndef INCLUDED_STRING_BUILDER_HPP
#define INCLUDED_STRING_BUILDER_HPP

#include <sstream>

namespace kj {

class StringBuilder
{
public:
    template<typename T>
    StringBuilder& operator<<(T&& value);
    template<typename Stream>
    StringBuilder& operator<<(Stream& (*func)(Stream&));
    operator std::string() const { return d_stream.str(); }
    template<typename... Args>
    static std::string build(Args&&... args);
private:
    static void doBuild(StringBuilder& sb);
    template<typename T, typename... Rest>
    static void doBuild(StringBuilder& sb, T&& arg, Rest&&... rest);
    template<typename Stream, typename... Rest>
    static void doBuild(StringBuilder& sb, Stream& (*func)(Stream&), Rest&&... rest);

    std::ostringstream d_stream;
};

template<typename T>
StringBuilder& StringBuilder::operator<<(T&& value)
{
    d_stream << std::forward<T>(value);
    return *this;
}
template<typename Stream>
StringBuilder& StringBuilder::operator<<(Stream& (*func)(Stream&))
{
    d_stream << func;
    return *this;
}

template<typename... Args>
std::string StringBuilder::build(Args&&... args)
{
    StringBuilder sb;
    doBuild(sb, std::forward<Args>(args)...);
    return sb;
}

void StringBuilder::doBuild(StringBuilder& sb)
{
    //Do nothing
}

template<typename T, typename... Rest>
void StringBuilder::doBuild(StringBuilder& sb, T&& arg, Rest&&... rest)
{
    sb << std::forward<T>(arg);
    doBuild(sb, std::forward<Rest>(rest)...);
}

template<typename Stream, typename... Rest>
void StringBuilder::doBuild(StringBuilder& sb, Stream& (*func)(Stream&), Rest&&... rest)
{
    sb << func;
    doBuild(sb, std::forward<Rest>(rest)...);
}

} // close namespace kj

#endif //INCLUDED_STRING_BUILDER_HPP
