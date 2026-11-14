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
