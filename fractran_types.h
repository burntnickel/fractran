#ifndef FRACTRAN_TYPES_H
#define FRACTRAN_TYPES_H

#include <cstdint>
#include <limits>
#include <vector>

using LargeIntType = std::uintmax_t;

constexpr auto kMaxInt = std::numeric_limits<LargeIntType>::max();

struct Fraction {
  LargeIntType numerator;
  LargeIntType denominator;
};

using FractranProgram = std::vector<Fraction>;

#endif
