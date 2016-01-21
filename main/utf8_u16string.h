#ifndef UTF8_U16STRING_H
#define UTF8_U16STRING_H

#include <string>
#include <utility>

namespace utf8_u16string {

constexpr const char16_t bad_u16_char = 0xd800;

std::pair<std::u16string, unsigned int> widen(const std::string& s);
std::pair<std::string, unsigned int> narrow(const std::u16string& s);
}

#endif
