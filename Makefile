# Copyright 2026 Jude Giampaolo
#
# This file is part of fractran.
#
# Alatar is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software Foundation,
# either version 3 of the License, or (at your option) any later version.
#
# Alatar is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with Alatar.
# If not, see <https://www.gnu.org/licenses/>.

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

	