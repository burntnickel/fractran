#include "util.h"

#include <algorithm>
#include <sstream>

// Trim white space from both ends and return a copy
std::string StringTrimCopy(std::string s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(),
          s.end());

  return s;
}

std::vector<std::string> Split(const std::string& string, char delim) {
  std::istringstream iss(string);
  std::string sub_string;
  std::vector<std::string> tokens;

  while (std::getline(iss, sub_string, delim)) {
    tokens.push_back(sub_string);
  }

  return tokens;
}

