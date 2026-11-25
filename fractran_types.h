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
