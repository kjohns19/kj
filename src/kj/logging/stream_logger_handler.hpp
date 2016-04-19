#ifndef INCLUDED_KJ_STREAM_LOGGER_HANDLER_HPP
#define INCLUDED_KJ_STREAM_LOGGER_HANDLER_HPP

#include <kj/logging/logger_handler.hpp>
#include <ostream>

namespace kj {

class StreamLoggerHandler : public kj::LoggerHandler
{
public:
    StreamLoggerHandler(std::ostream& stream);
private:
    void log(const std::string& message) override;

    std::ostream* d_stream;
};

} // close namespace kj

#endif //INCLUDED_KJ_STREAM_LOGGER_HANDLER_HPP
