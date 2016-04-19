#include <kj/logging/logger.hpp>
#include <algorithm>

namespace kj {

namespace {

thread_local Logger* s_logger;

}

Logger& Logger::logger()
{
    if (!s_logger)
    {
        static Logger logger;
        s_logger = &logger;
    }
    return *s_logger;
}
void Logger::logger(Logger& logger)
{
    s_logger = &logger;
}

Logger::Logger()
: d_minLevel(INFO) {}

const char* Logger::levelString(int level)
{
    switch(level)
    {
        case Logger::DEBUG:
            return "DEBUG";
        case Logger::INFO:
            return "INFO ";
        case Logger::WARN:
            return "WARN ";
        case Logger::ERROR:
            return "ERROR";
        case Logger::FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
    }
}

void Logger::addHandler(LoggerHandler& handler)
{
    d_handlers.push_back(&handler);
}
void Logger::removeHandler(LoggerHandler& handler)
{
    d_handlers.erase(
        std::remove(d_handlers.begin(), d_handlers.end(), &handler),
        d_handlers.end());
}

int Logger::minLevel() const
{
    return d_minLevel;
}
void Logger::minLevel(int level)
{
    d_minLevel = level;
}

} // close namespace kj

