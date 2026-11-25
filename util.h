// Copyright 2026 Jude Giampaolo
//
// This file is part of fractran.
//
// Alatar is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Alatar is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with Alatar.
// If not, see <https://www.gnu.org/licenses/>.

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

