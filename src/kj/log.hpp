#ifndef INCLUDED_KJ_LOG_HPP
#define INCLUDED_KJ_LOG_HPP

#include <kj/logging/logger.hpp>

namespace kj {
namespace log {

using Level = kj::Logger::Level;

template<typename... Args>
void log(Level level, Args&&... args)
{
    kj::Logger& logger = kj::Logger::logger();
    logger.log(level, std::forward<Args>(args)...);
}

template<typename... Args>
void debug(Args&&... args)
{
    log(Level::DEBUG, std::forward<Args>(args)...);
}
template<typename... Args>
void info(Args&&... args)
{
    log(Level::INFO, std::forward<Args>(args)...);
}
template<typename... Args>
void warn(Args&&... args)
{
    log(Level::WARN, std::forward<Args>(args)...);
}
template<typename... Args>
void error(Args&&... args)
{
    log(Level::ERROR, std::forward<Args>(args)...);
}
template<typename... Args>
void fatal(Args&&... args)
{
    log(Level::FATAL, std::forward<Args>(args)...);
}

} // close namespace log
} // close namespace kj

#endif //INCLUDED_KJ_LOG_HPP
