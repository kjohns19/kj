#ifndef INCLUDED_KJ_FONT_UTIL_HPP
#define INCLUDED_KJ_FONT_UTIL_HPP

#include <string>
#include <vector>

namespace kj {
namespace FontUtil {

bool loadSystemFonts();
bool getFontFilename(
        const std::string& family,
        const std::string& style,
        std::string* filename);
bool getFontFamilies(std::vector<std::string>* families);
bool getFontStyles(const std::string& family, std::vector<std::string>* styles);

} // close namespace FontUtil
} // close namespace kj

#endif //INCLUDED_KJ_FONT_UTIL_HPP
