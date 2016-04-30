#ifndef INCLUDED_KJ_LOGGER_HPP
#define INCLUDED_KJ_LOGGER_HPP

#include <kj/string_builder.hpp>
#include <kj/logging/logger_handler.hpp>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>

namespace kj {

class Logger
{
public:
    static Logger& logger();
    static void logger(Logger& logger);
    static const char* levelString(int level);

    enum Level { DEBUG, TRACE, INFO, WARN, ERROR, FATAL };

    Logger();

    template<typename... Args>
    void log(int level, const char* file, const char* func, int line, Args&&... args);

    void addHandler(LoggerHandler& handler);
    void removeHandler(LoggerHandler& handler);

    int minLevel() const;
    void minLevel(int level);

    int maxLevel() const;
    void maxLevel(int level);
private:
    std::vector<LoggerHandler*> d_handlers;
    int d_minLevel;
    int d_maxLevel;
};

template<typename... Args>
void Logger::log(int level, const char* file, const char* func, int line, Args&&... args)
{
    if (level >= d_minLevel && level <= d_maxLevel)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_t = std::chrono::system_clock::to_time_t(now);
        std::string message = kj::StringBuilder::build(std::forward<Args>(args)...);
        for(auto handler: d_handlers)
            handler->log(level, file, func, line, now_t, message);
    }
}

} // close namespace kj

#endif //INCLUDED_KJ_LOGGER_HPP
