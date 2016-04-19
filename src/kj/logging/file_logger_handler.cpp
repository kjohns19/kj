#include <kj/logging/file_logger_handler.hpp>

namespace kj {

FileLoggerHandler::FileLoggerHandler(
        const std::string& filename,
        std::ios_base::openmode mode)
: d_file(filename, mode) {}

void FileLoggerHandler::log(const std::string& message)
{
    d_file << message << std::flush;
}

} // close namespace kj

