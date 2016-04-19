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

    enum Level { DEBUG, INFO, WARN, ERROR, FATAL };

    Logger();

    template<typename... Args>
    void log(int level, Args&&... args);

    void addHandler(LoggerHandler& handler);
    void removeHandler(LoggerHandler& handler);

    int minLevel() const;
    void minLevel(int level);
private:
    std::vector<LoggerHandler*> d_handlers;
    int d_minLevel;
};

template<typename... Args>
void Logger::log(int level, Args&&... args)
{
    if (level >= d_minLevel)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_t = std::chrono::system_clock::to_time_t(now);
        std::string message = kj::StringBuilder::build(std::forward<Args>(args)...);
        for(auto handler: d_handlers)
            handler->log(level, now_t, message);
    }
}

} // close namespace kj

#endif //INCLUDED_KJ_LOGGER_HPP
