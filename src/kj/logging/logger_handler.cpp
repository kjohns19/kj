#include <kj/logging/logger_handler.hpp>
#include <kj/logging/logger_formatter.hpp>
#include <kj/logging/logger.hpp>

namespace kj {

LoggerFormatter LoggerHandler::s_defaultFormatter;

LoggerHandler::LoggerHandler()
: d_formatter(&s_defaultFormatter)
, d_minLevel(Logger::INFO) {}
LoggerHandler::LoggerHandler(int minLevel)
: d_formatter(&s_defaultFormatter)
, d_minLevel(minLevel) {}

void LoggerHandler::log(int level, std::time_t time, const std::string& message)
{
    if (level >= d_minLevel)
        log(d_formatter->format(level, time, message));
}

int LoggerHandler::minLevel() const
{
    return d_minLevel;
}
void LoggerHandler::minLevel(int level)
{
    d_minLevel = level;
}

const LoggerFormatter& LoggerHandler::formatter() const
{
    return *d_formatter;
}
void LoggerHandler::formatter(const LoggerFormatter& formatter)
{
    d_formatter = &formatter;
}

} // close namespace kj

