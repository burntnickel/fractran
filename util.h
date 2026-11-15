#ifndef FRACTRAN_UTIL_H
#define FRACTRAN_UTIL_H

#include <string>
#include <vector>

// Trim white space from both ends and return a copy
std::string StringTrimCopy(std::string s);

std::vector<std::string> Split(const std::string& string, char delim);

void RemoveAllWhiteSpace(std::string& s);

#endif
