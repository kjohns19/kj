#ifndef INCLUDED_KJ_LOG_HPP
#define INCLUDED_KJ_LOG_HPP

#include <kj/logging/logger.hpp>

#define KJ_LOG_LOG(level, ...) \
    kj::log::log(level, __FILE__, __func__, __LINE__, __VA_ARGS__)
#define KJ_LOG_DEBUG(...) KJ_LOG_LOG(kj::Logger::DEBUG, __VA_ARGS__)
#define KJ_LOG_TRACE(...) KJ_LOG_LOG(kj::Logger::TRACE, __VA_ARGS__)
#define KJ_LOG_INFO(...)  KJ_LOG_LOG(kj::Logger::INFO , __VA_ARGS__)
#define KJ_LOG_WARN(...)  KJ_LOG_LOG(kj::Logger::WARN , __VA_ARGS__)
#define KJ_LOG_ERROR(...) KJ_LOG_LOG(kj::Logger::ERROR, __VA_ARGS__)
#define KJ_LOG_FATAL(...) KJ_LOG_LOG(kj::Logger::FATAL, __VA_ARGS__)

namespace kj {
namespace log {

template<typename... Args>
void log(
        kj::Logger::Level level,
        const char* file, const char* func, int line,
        Args&&... args)
{
    kj::Logger& logger = kj::Logger::logger();
    logger.log(level, file, func, line, std::forward<Args>(args)...);
}

} // close namespace log
} // close namespace kj

#endif //INCLUDED_KJ_LOG_HPP
