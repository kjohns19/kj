#ifndef INCLUDED_KJ_LOGGER_HANDLER_HPP
#define INCLUDED_KJ_LOGGER_HANDLER_HPP

#include <string>
#include <ctime>

namespace kj {

class LoggerFormatter;

class LoggerHandler
{
public:
    LoggerHandler();
    LoggerHandler(int minLevel);
    LoggerHandler(int minLevel, int maxLevel);

    void log(
            int level,
            const char* file, const char* func, int line,
            std::time_t time,
            const std::string& message);

    int minLevel() const;
    void minLevel(int level);

    int maxLevel() const;
    void maxLevel(int level);

    const LoggerFormatter& formatter() const;
    void formatter(const LoggerFormatter& formatter);
private:
    virtual void log(const std::string& message) = 0;

    const LoggerFormatter* d_formatter;
    int d_minLevel;
    int d_maxLevel;
};

} // close namespace kj

#endif //INCLUDED_KJ_LOGGER_HANDLER_HPP
