#include "command_line.h"

#include <cstring>
#include <iostream>

std::optional<CommandLineArgs> GetCommandLine(int argc, char* argv[]) {
  CommandLineArgs tmp_args;
  int cur_arg_idx = 1;
  bool got_filename = false;

  while (cur_arg_idx < argc) {
    std::cout << argv[cur_arg_idx] << "\n";

    if (got_filename) {
      std::cerr << "Unexpected arguements following filename\n";
      return {};
    }

    if (argv[cur_arg_idx][0] == '-') {
      if (strcmp("-v", argv[cur_arg_idx]) == 0) {
        ++cur_arg_idx;

        if (cur_arg_idx < argc) {
          tmp_args.inital_value_opt = std::stoull(argv[cur_arg_idx]);
        } else {
          std::cerr << "Missing arguement for -v\n";
          return {};
        }
      } else if (strcmp("-i", argv[cur_arg_idx]) == 0) {
        ++cur_arg_idx;

        if (cur_arg_idx < argc) {
          tmp_args.max_iterations_opt = std::stoull(argv[cur_arg_idx]);
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

