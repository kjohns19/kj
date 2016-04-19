#ifndef INCLUDED_KJ_LOGGER_FORMATTER_HPP
#define INCLUDED_KJ_LOGGER_FORMATTER_HPP

#include <ctime>
#include <string>

namespace kj {

class LoggerFormatter
{
public:
    LoggerFormatter() {}

    std::string format(int level, std::time_t time, const std::string& message) const;
private:
};

} // close namespace kj

#endif //INCLUDED_KJ_LOGGER_FORMATTER_HPP
