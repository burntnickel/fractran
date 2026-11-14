CXX = g++

CXXFLAGS = -std=c++20 -g
LDFLAGS =
LDLIBS =

TARGET = fractran

SRCS = fractran.cc fractran_message.cc util.cc command_line.cc

CXXFLAGS += -Wall -Wextra -Wwrite-strings -Wno-parentheses -Wpedantic -Wdeprecated
CXXFLAGS += -Wsign-conversion -Wimplicit-fallthrough -Wshadow -Warray-bounds
CXXFLAGS += -Wmissing-braces -Wconversion -Wuseless-cast
LDFLAGS  +=
LDLIBS   +=

OBJS = $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LDLIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

	