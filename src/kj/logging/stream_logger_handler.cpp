#include <kj/logging/stream_logger_handler.hpp>

namespace kj {

StreamLoggerHandler::StreamLoggerHandler(std::ostream& stream)
: d_stream(&stream) {}

void StreamLoggerHandler::log(const std::string& message)
{
    (*d_stream) << message << std::flush;
}

} // close namespace kj

