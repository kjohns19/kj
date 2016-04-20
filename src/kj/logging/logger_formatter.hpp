#ifndef INCLUDED_KJ_LOGGER_FORMATTER_HPP
#define INCLUDED_KJ_LOGGER_FORMATTER_HPP

#include <ctime>
#include <string>
#include <vector>
#include <functional>

namespace kj {

class LoggerFormatter
{
public:
    LoggerFormatter();
    LoggerFormatter(const std::string& formatString);

    std::string format(int level, std::time_t time, const std::string& message) const;
private:
    std::vector<std::function<std::string(
            int level,
            std::time_t time,
            const std::string& message)>> d_formats;
};

} // close namespace kj

#endif //INCLUDED_KJ_LOGGER_FORMATTER_HPP
