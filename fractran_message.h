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
