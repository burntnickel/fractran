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


#include "command_line.h"
#include "util.h"

#include <cstring>
#include <iostream>

std::optional<CommandLineArgs> GetCommandLine(int argc, char* argv[]) {
  CommandLineArgs tmp_args;
  int cur_arg_idx = 1;
  bool got_filename = false;

  while (cur_arg_idx < argc) {
    if (got_filename) {
      std::cerr << "Unexpected arguments following filename\n";
      return {};
    }

    if (argv[cur_arg_idx][0] == '-') {
      if (strcmp("-v", argv[cur_arg_idx]) == 0) {
        ++cur_arg_idx;

        if (cur_arg_idx < argc) {
          tmp_args.inital_value_opt = StoullNoThrow(argv[cur_arg_idx]);

          if (!tmp_args.inital_value_opt) {
            std::cerr << "Invalid arguement for -v: '" << argv[cur_arg_idx] << "'\n";
            return {};
          }
        } else {
          std::cerr << "Missing arguement for -v\n";
          return {};
        }
      } else if (strcmp("-i", argv[cur_arg_idx]) == 0) {
        ++cur_arg_idx;

        if (cur_arg_idx < argc) {
          tmp_args.max_iterations_opt = StoullNoThrow(argv[cur_arg_idx]);

          if (!tmp_args.max_iterations_opt) {
            std::cerr << "Invalid arguement for -i: '" << argv[cur_arg_idx] << "'\n";
            return {};
          }
        } else {
          std::cerr << "Missing arguement for -i\n";
          return {};
        }
      } else {
        std::cerr << "Unknown parameter '" << argv[cur_arg_idx] << "'\n";
        return {};
      }
    } else {
      tmp_args.filename = argv[cur_arg_idx];
      got_filename = true;
    }

    ++cur_arg_idx;
  }

  if (!got_filename) {
    std::cerr << "Missing filename for program\n";
    return {};
  }

  return tmp_args;
}
