#include <kj/logging/logger_formatter.hpp>
#include <kj/logging/logger.hpp>
#include <kj/string_builder.hpp>
#include <iomanip>

namespace kj {

std::string LoggerFormatter::format(
        int level,
        std::time_t time,
        const std::string& message) const
{
    std::tm tm;
    localtime_r(&time, &tm);
    return StringBuilder::build(
        "[", std::put_time(&tm, "%T"), ": ",
        Logger::levelString(level), "]: ", message, "\n");
}

} // close namespace kj

