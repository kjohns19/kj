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

    void log(int level, std::time_t time, const std::string& message);

    int minLevel() const;
    void minLevel(int level);

    const LoggerFormatter& formatter() const;
    void formatter(const LoggerFormatter& formatter);
private:
    virtual void log(const std::string& message) = 0;

    static LoggerFormatter s_defaultFormatter;

    const LoggerFormatter* d_formatter;
    int d_minLevel;
};

} // close namespace kj

#endif //INCLUDED_KJ_LOGGER_HANDLER_HPP
