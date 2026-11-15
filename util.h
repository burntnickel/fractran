#ifndef FRACTRAN_UTIL_H
#define FRACTRAN_UTIL_H

#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

// Trim white space from both ends and return a copy
std::string StringTrimCopy(std::string s);

std::vector<std::string> Split(const std::string& string, char delim);

void RemoveAllWhiteSpace(std::string& s);

std::optional<char> InvalidCharCheck(std::string_view s, std::string_view valid_chars);

// Get the return type from std::stoull
using StoullReturnType = decltype(std::stoull(std::declval<std::string>()));

// The second option return a message describing why the conversion failed
std::optional<StoullReturnType> StoullNoThrow(const std::string& s);
std::optional<StoullReturnType> StoullNoThrow(const std::string& s, std::string& msg);

#endif

