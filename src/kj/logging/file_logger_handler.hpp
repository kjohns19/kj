#ifndef INCLUDED_KJ_FILE_LOGGER_HANDLER_HPP
#define INCLUDED_KJ_FILE_LOGGER_HANDLER_HPP

#include <kj/logging/logger_handler.hpp>
#include <fstream>

namespace kj {

class FileLoggerHandler : public kj::LoggerHandler
{
public:
    FileLoggerHandler(
            const std::string& filename,
            std::ios_base::openmode mode = std::ios_base::out);
private:
    void log(const std::string& message) override;

    std::ofstream d_file;
};

} // close namespace kj

#endif //INCLUDED_KJ_FILE_LOGGER_HANDLER_HPP
