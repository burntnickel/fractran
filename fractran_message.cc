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

