#ifndef FRACTRAN_UTIL_H
#define FRACTRAN_UTIL_H

#include <optional>
#include <string>
#include <string_view>
#include <vector>

// Trim white space from both ends and return a copy
std::string StringTrimCopy(std::string s);

std::vector<std::string> Split(const std::string& string, char delim);

void RemoveAllWhiteSpace(std::string& s);

std::optional<char> InvalidCharCheck(std::string_view s, std::string_view valid_chars);

#endif
