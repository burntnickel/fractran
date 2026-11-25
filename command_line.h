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

#ifndef FRACTRAN_COMMAND_LINE_H
#define FRACTRAN_COMMAND_LINE_H

#include "fractran_types.h"

#include <optional>
#include <string>

struct CommandLineArgs {
  std::string filename;
  std::optional<LargeIntType> inital_value_opt{};
  std::optional<LargeIntType> max_iterations_opt{};
};

std::optional<CommandLineArgs> GetCommandLine(int argc, char* argv[]);

#endif
