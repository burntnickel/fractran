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

#ifndef FRACTRAN_MESSAGE_H
#define FRACTRAN_MESSAGE_H

#include <string>

struct MessageContext {
  std::string filename;
  int line_number;
};

enum MessageType { kWarning, kError };

void Message(MessageContext context, std::string_view message, MessageType message_type);

#endif
