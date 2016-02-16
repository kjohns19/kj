#include <kj/font_util.hpp>
#include <kj/string_util.hpp>
#include <kj/finally.hpp>
#include <kj/timer.hpp>
#include <cstdlib>
#include <map>
#include <sstream>
#include <iostream>

namespace kj {
namespace FontUtil {

namespace {

std::map<std::string, std::map<std::string, std::string>> s_fontData;

bool loadSystemFontsOnce();

} // close anonymous namespace


bool loadSystemFonts()
{
    static bool result = loadSystemFontsOnce();
    return result;
}

bool getFontFilename(
        const std::string& family,
        const std::string& style,
        std::string* filename)
{
    if (!loadSystemFonts())
        return false;

    auto search = s_fontData.find(family);
    if (search == s_fontData.end())
        return false;
    auto& stylemap = search->second;
    auto stylesearch = stylemap.find(style);
    if (stylesearch == stylemap.end())
        return false;
    *filename = stylesearch->second;
    return true;
}

bool getFontFamilies(std::vector<std::string>* families)
{
    if (!loadSystemFonts())
        return false;
    families->clear();
    for(auto& familyPair: s_fontData)
        families->push_back(familyPair.first);
    return true;
}
bool getFontStyles(const std::string& family, std::vector<std::string>* styles)
{
    if (!loadSystemFonts())
        return false;

    auto search = s_fontData.find(family);
    if (search == s_fontData.end())
        return false;

    styles->clear();
    for(auto& stylePair: search->second)
        styles->push_back(stylePair.first);

    return true;
}


namespace {

bool readline(FILE* file, std::string* line);

bool loadSystemFontsOnce()
{
    FILE* pipe = popen("fc-list -f \"%{file}|%{family}|%{style}\n\"", "r");
    auto close = kj::finally([pipe]() { pclose(pipe); });

    std::string line;
    std::string filename;
    std::string familyname;
    std::string stylestr;
    std::string style;
    while(readline(pipe, &line))
    {
        std::istringstream stream(line);
        std::getline(stream, filename,   '|');
        std::getline(stream, familyname, '|');
        std::getline(stream, stylestr,   '|');
        std::istringstream stylestream(stylestr);
        std::getline(stylestream, style, ',');
        s_fontData[familyname][style] = filename;
    }

    return true;
}

bool readline(FILE* file, std::string* line)
{
    static const size_t bufsz = 256;
    char buffer[bufsz];
    line->clear();
    bool didRead = false;

    while(fgets(buffer, bufsz, file))
    {
        (*line) += buffer;
        if (line->back() == '\n')
        {
            line->pop_back();
            return true;
        }
        didRead = true;
    }
    return didRead;
}

} // close anonymous namespace

} // close namespace FontUtil
} // close namespace kj

