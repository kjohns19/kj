#include <kj/logging/logger_formatter.hpp>
#include <kj/logging/logger.hpp>
#include <kj/string_builder.hpp>
#include <iomanip>
#include <sstream>
#include <iostream>

namespace kj {

namespace {

struct Args
{
    int level;
    const char* file;
    const char* func;
    int line;
    std::time_t time;
    const std::string& message;
};

struct StringFormat
{
    StringFormat(const std::string& string)
    : d_string(string) {}

    void operator()(std::ostream& stream, const void* args) const
    {
        stream << d_string;
    }

    std::string d_string;
};

struct TimeFormat
{
    TimeFormat(const std::string& format)
    : d_format(format) {}

    void operator()(std::ostream& stream, const void* args) const
    {
        std::tm tm;
        localtime_r(&static_cast<const Args*>(args)->time, &tm);
        stream << std::put_time(&tm, d_format.c_str());
    }

    std::string d_format;
};

}

LoggerFormatter::LoggerFormatter()
: LoggerFormatter("[$T:$L] $M") {}
LoggerFormatter::LoggerFormatter(const std::string& formatString)
{
    size_t start = 0;
    while(start != std::string::npos)
    {
        size_t pos = formatString.find('$', start);
        if (pos == std::string::npos || pos == formatString.length()-1)
            d_formats.push_back(StringFormat(formatString.substr(start)));
        else
        {
            if (pos != start)
                d_formats.push_back(StringFormat(formatString.substr(start, pos-start)));

            char c = formatString[pos+1];
            switch(c)
            {
                case 'T':
                    d_formats.push_back(TimeFormat("%T"));
                    break;
                case 'L':
                    d_formats.push_back([](std::ostream& stream, const void* args) {
                        int level = static_cast<const Args*>(args)->level;
                        stream << std::setw(5) << kj::Logger::levelString(level);
                    });
                    break;
                case 'M':
                    d_formats.push_back([](std::ostream& stream, const void* args) {
                        stream << static_cast<const Args*>(args)->message;
                    });
                    break;
                case 'f':
                    d_formats.push_back([](std::ostream& stream, const void* args) {
                        stream << static_cast<const Args*>(args)->file;
                    });
                    break;
                case 'F':
                    d_formats.push_back([](std::ostream& stream, const void* args) {
                        stream << static_cast<const Args*>(args)->func;
                    });
                    break;
                case 'l':
                    d_formats.push_back([](std::ostream& stream, const void* args) {
                        stream << static_cast<const Args*>(args)->line;
                    });
                default:
                    d_formats.push_back(StringFormat(std::string(c, 1)));
                    break;
            }
            pos+=2;
            if (pos == formatString.length())
                pos = std::string::npos;
        }
        start = pos;
    }
}

std::string LoggerFormatter::format(
            int level,
            const char* file, const char* func, int line,
            std::time_t time,
            const std::string& message) const
{
    std::ostringstream stream;

    Args args{level, file, func, line, time, message};

    for(auto& format: d_formats)
        format(stream, &args);
    stream << "\n";

    return stream.str();
}

} // close namespace kj

