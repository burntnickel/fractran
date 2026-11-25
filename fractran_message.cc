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

#include "fractran_message.h"

#include <iostream>

void Message(MessageContext context, std::string_view message, MessageType message_type) {
  std::string type_str;

  switch (message_type) {
    case kWarning:
      type_str = "warning";
      break;
    case (kError):
      type_str = "error";
      break;
  }

  std::cerr << context.filename << ":" << context.line_number << ": " << type_str << ": " << message << "\n";
}

