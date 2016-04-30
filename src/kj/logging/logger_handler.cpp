#include <kj/logging/logger_handler.hpp>
#include <kj/logging/logger_formatter.hpp>
#include <kj/logging/logger.hpp>

namespace kj {

namespace {

LoggerFormatter s_defaultFormatter;

} // close anonymous namespace

LoggerHandler::LoggerHandler()
: d_formatter(&s_defaultFormatter)
, d_minLevel(Logger::INFO)
, d_maxLevel(Logger::FATAL) {}
LoggerHandler::LoggerHandler(int minLevel)
: d_formatter(&s_defaultFormatter)
, d_minLevel(minLevel)
, d_maxLevel(Logger::FATAL) {}
LoggerHandler::LoggerHandler(int minLevel, int maxLevel)
: d_formatter(&s_defaultFormatter)
, d_minLevel(minLevel)
, d_maxLevel(maxLevel) {}

void LoggerHandler::log(
        int level,
        const char* file, const char* func, int line,
        std::time_t time,
        const std::string& message)
{
    if (level >= d_minLevel && level <= d_maxLevel)
        log(d_formatter->format(level, file, func, line, time, message));
}

int LoggerHandler::minLevel() const
{
    return d_minLevel;
}
void LoggerHandler::minLevel(int level)
{
    d_minLevel = level;
}

int LoggerHandler::maxLevel() const
{
    return d_maxLevel;
}
void LoggerHandler::maxLevel(int level)
{
    d_maxLevel = level;
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

