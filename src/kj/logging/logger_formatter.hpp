#ifndef INCLUDED_KJ_LOGGER_FORMATTER_HPP
#define INCLUDED_KJ_LOGGER_FORMATTER_HPP

#include <ctime>
#include <string>
#include <vector>
#include <ostream>
#include <functional>

namespace kj {

class LoggerFormatter
{
public:
    LoggerFormatter();
    LoggerFormatter(const std::string& formatString);

    std::string format(
            int level,
            const char* file, const char* func, int line,
            std::time_t time,
            const std::string& message) const;
private:
    std::vector<std::function<void(std::ostream&, const void*)>> d_formats;
};

} // close namespace kj

#endif //INCLUDED_KJ_LOGGER_FORMATTER_HPP
