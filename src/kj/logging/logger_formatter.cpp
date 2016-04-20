#include <kj/logging/logger_formatter.hpp>
#include <kj/logging/logger.hpp>
#include <kj/string_builder.hpp>
#include <iomanip>
#include <sstream>
#include <iostream>

namespace kj {

namespace {

struct StringFormat
{
    StringFormat(const std::string& string)
    : d_string(string) {}

    std::string operator()(int level, std::time_t time, const std::string& message) const
    {
        return d_string;
    }

    std::string d_string;
};

struct TimeFormat
{
    TimeFormat(const std::string& format)
    : d_format(format) {}

    std::string operator()(int level, std::time_t time, const std::string& message) const
    {
        std::tm tm;
        localtime_r(&time, &tm);
        return kj::StringBuilder() << std::put_time(&tm, d_format.c_str());
    }

    std::string d_format;
};

std::string levelFormat(int level, std::time_t time, const std::string& message)
{
    return kj::StringBuilder() << std::setw(5) << kj::Logger::levelString(level);
}
std::string messageFormat(int level, std::time_t time, const std::string& message)
{
    return message;
}

}

LoggerFormatter::LoggerFormatter()
: LoggerFormatter("[$T: $L]: $M") {}
LoggerFormatter::LoggerFormatter(const std::string& formatString)
{
    size_t start = 0;
    while(start != std::string::npos)
    {
        size_t pos = formatString.find('$', start);
        if (pos == std::string::npos || pos == formatString.length()-1)
        {
            d_formats.push_back(StringFormat(formatString.substr(start)));
        }
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
                    d_formats.push_back(levelFormat);
                    break;
                case 'M':
                    d_formats.push_back(messageFormat);
                    break;
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
        std::time_t time,
        const std::string& message) const
{
    std::ostringstream stream;

    for(auto& format: d_formats)
        stream << format(level, time, message);
    stream << "\n";

    return stream.str();
}

} // close namespace kj

