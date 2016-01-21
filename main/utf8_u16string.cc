#include <string>
#include <utility>
using namespace std;

#include "utf8_u16string.h"

namespace utf8_u16string {

pair<char16_t, unsigned int>
widen(string::const_iterator cit, const string::const_iterator cend) {
  if (cit == cend)
    return pair<char16_t, unsigned int>(bad_u16_char, 0);
  const unsigned char c0 = static_cast<unsigned char>(*cit);
  if (c0 < 0x80)
    return pair<char16_t, unsigned int>(*cit, 1);
  if (++cit == cend)
    return pair<char16_t, unsigned int>(bad_u16_char, 0);
  const unsigned char c1 = static_cast<unsigned char>(*cit);
  if ((c0 & 0xe0) == 0xc0) {
    if (c1 < 0x80 || c1 > 0xbf)
      return pair<char16_t, unsigned int>(bad_u16_char, 0);
    return pair<char16_t, unsigned int>((c0 & 0x1f) << 6 | (c1 & 0x3f), 2);
  }
  if (++cit == cend)
    return pair<char16_t, unsigned int>(bad_u16_char, 0);
  const unsigned char c2 = static_cast<unsigned char>(*cit);
  if ((c0 & 0xe0) == 0xe0) {
    if (c1 < 0x80 || c1 > 0xbf || c2 < 0x80 || c2 > 0xbf)
      return pair<char16_t, unsigned int>(bad_u16_char, 0);
    return pair<char16_t, unsigned int>((c0 & 0x0f) << 12 | (c1 & 0x3f) << 6 | (c2 & 0x3f), 3);
  }
  return pair<char16_t, unsigned int>(bad_u16_char, 0);
}

pair<u16string, unsigned int>
widen(const string& s) {
  u16string u16s;
  const string::const_iterator cend = s.end();
  string::const_iterator cit = s.begin();
  do {
    const auto widened = widen(cit, cend);
    if (widened.first == bad_u16_char)
      return pair<u16string, unsigned int>(u16s, cit - s.begin());
    u16s.push_back(widened.first);
    cit += widened.second;
  } while (cit != cend);
  return pair<u16string, unsigned int>(u16s, cit - s.begin());
}

pair<string, unsigned int>
narrow(const u16string& u16s) {
  string s;
  const u16string::const_iterator cend = u16s.end();
  for (u16string::const_iterator cit = u16s.begin(); cit != cend; ++cit) {
    if (*cit <= 0x7f)
      s.push_back(static_cast<char>(*cit));
    else if (*cit <= 0x7ff) {
      s.push_back(0xc0 | ((*cit >> 6) & 0x1f));
      s.push_back(0x80 | (*cit & 0x3f));
    } else if (*cit < 0xd800 || *cit > 0xdfff) {
      s.push_back(0xe0 | ((*cit >> 12) & 0x0f));
      s.push_back(0x80 | ((*cit >> 6) & 0x3f));
      s.push_back(0x80 | (*cit & 0x3f));
    } else
      return pair<string, unsigned int>(s, cit - u16s.begin());
  }
  return pair<string, unsigned int>(s, cend - u16s.begin());
}
}
