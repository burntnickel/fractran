#include "command_line.h"
#include "fractran_message.h"
#include "fractran_types.h"
#include "util.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

// TODO: Add bigint support (an optional flag to use?)
// TODO: Add catch for throwing conversions

static void PrintUsage(void) {
  std::cerr << "Usage: fractran [-v intial_value] [-i max_iterations] <filename>\n";
}

static bool ValidCharCheck(std::string s, std::string valid_chars, MessageContext context) {
  size_t invalid_pos = s.find_first_not_of(valid_chars);

  if (invalid_pos == std::string::npos) {
    return true;
  }

  Message(context, std::string("unexpected charater '") + s[invalid_pos] + "' found in '" + s + "'",
               kError);

  return false;
}

static bool ProcessFracString(std::string s, MessageContext context, Fraction& the_fraction) {
  // Remove all white space
  s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char x) { return std::isspace(x); }), s.end());

  // Check for valid characters
  if (!ValidCharCheck(s, "//0123456789", context)) {
    return false;
  }

  if (s.find('/') == std::string::npos) {
    Message(context, "missing '/' in fraction '" + s + "'", kError);
    return false;
  }

  // Split on /
  auto frac_strings = Split(s, '/');

  if (frac_strings.size() != 2) {
    Message(context, "more than one '/' found in '" + s + "'", kError);
  }

  // Convert integers and populate fraction
  the_fraction.numerator = std::stoull(frac_strings[0]);
  the_fraction.denominator = std::stoull(frac_strings[1]);

  if (std::gcd(the_fraction.numerator, the_fraction.denominator) != 1) {
    Message(context, s + " is not in lowest terms", kWarning);
  }

  return true;
}

static bool ReadFractionLine(std::string line, MessageContext context, FractranProgram& program,
                             bool& complete) {
  if (line.empty()) {
    return true;
  }

  // Check for closing ')', any text after that is an error
  auto close_paren_loc = line.find(')');

  if (close_paren_loc != std::string::npos) {
    if (close_paren_loc == (line.size() - 1)) {
      // Remove the ')' and set complete flag
      complete = true;
      line.pop_back();
    } else {
      // If there is extra text after the program end
      Message(
          context,
          std::string("unexpected text after program complete: '") + line.substr(close_paren_loc + 1) + "'",
          kError);
      return false;
    }
  }

  auto frac_strings = Split(line, ',');

  for (std::string frac_candidate : frac_strings) {
    Fraction the_fraction;

    bool valid = ProcessFracString(frac_candidate, context, the_fraction);

    if (!valid) {
      return false;
    }

    program.push_back(the_fraction);
  }

  return true;
}

static std::optional<FractranProgram> LoadProgram(std::filesystem::path path) {
  std::ifstream in(path);

  if (!in.is_open()) {
    std::cerr << "Failed to open: " << path << " : " << std::strerror(errno) << "\n";
    return {};
  }

  bool done_reading = false;
  int line_number = 0;
  bool in_program = false;
  bool prog_complete = false;
  FractranProgram tmp_prog;

  while (!done_reading) {
    std::string next_line;

    std::getline(in, next_line);
    ++line_number;

    if (!in) {
      done_reading = true;
    } else {
      // Skip blank lines
      if (next_line.length() > 0) {
        std::string tmp_str = StringTrimCopy(next_line);

        // Skip comment lines
        if (tmp_str[0] != '#') {
          MessageContext context{path.filename().string(), line_number};

          if (in_program) {
            bool line_valid = ReadFractionLine(tmp_str, context, tmp_prog, prog_complete);

            if (!line_valid) {
              return {};
            }

            if (prog_complete) {
              in_program = false;
            }
          } else {
            if (prog_complete) {
              // If we've already completed a program we shouldn't see an new charaters
              Message(context, std::string("program already complete, found '") + tmp_str[0] + "'",
                           kError);
              return {};
            }

            if (tmp_str[0] == '(') {
              in_program = true;

              bool line_valid = ReadFractionLine(tmp_str.substr(1), context, tmp_prog, prog_complete);

              if (!line_valid) {
                return {};
              }

              if (prog_complete) {
                in_program = false;
              }
            } else {
              // The only non-comment, non-white space chararter that is valid if not in a program is '('
              Message(context, std::string("expected '(' found '") + tmp_str[0] + "'", kError);
              return {};
            }
          }
        }
      }
    }
  }

  in.close();

  return tmp_prog;
}

static LargeIntType GetInitialValue(void) {
  std::cout << "Input inital value for program: ";

  std::string tmp;
  std::cin >> tmp;
  std::cout << "\n";

  return std::stoull(tmp);
}

static void RunProgram(const FractranProgram& p, LargeIntType v, LargeIntType max_itr) {
  bool done = false;
  LargeIntType n = v;
  auto prog_len = p.size();
  LargeIntType itr = 1;

  while (!done) {
    std::cout << itr << "    " << n << "\n";

    bool match = false;
    done = true;

    for (unsigned int ii = 0; ii < prog_len; ++ii) {
      match = ((n % p[ii].denominator) == 0);

      if (match) {
        done = false;
        n = n / p[ii].denominator;

        // Check to see if we'll overflow / wrap-around
        if ((p[ii].numerator > 0) && (n > (kMaxInt / p[ii].numerator))) {
          std::cerr << "Computation overflowed at this iteration\n";
          return;
        }

        n = n * p[ii].numerator;
        break;
      }
    }

    done = (itr >= max_itr);

    ++itr;
  }
}

int main(int argc, char* argv[]) {
  std::optional<CommandLineArgs> command_line_opt = GetCommandLine(argc, argv);

  if (!command_line_opt) {
    PrintUsage();
    return EXIT_FAILURE;
  }

  CommandLineArgs command_line = command_line_opt.value();

  std::optional<FractranProgram> the_program_opt = LoadProgram(command_line.filename);

  if (!the_program_opt) {
    return EXIT_FAILURE;
  }

  LargeIntType initial_value;
  LargeIntType max_itr;

  if (command_line.inital_value_opt) {
    initial_value = command_line.inital_value_opt.value();
  } else {
    initial_value = GetInitialValue();
  }

  if (command_line.max_iterations_opt) {
    max_itr = command_line.max_iterations_opt.value();
  } else {
    max_itr = kMaxInt;
  }

  RunProgram(the_program_opt.value(), initial_value, max_itr);

  return EXIT_SUCCESS;
}
