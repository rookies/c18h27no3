#  makefile
#  
#  Copyright 2012 Robert Knauer <robert@privatdemail.net>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  

### OPTIONS
## Target:
TARGET = game
## Object-Files:
OBJECTS = build/main.cpp.o \
          build/game.cpp.o \
          build/padding_data_calculator.cpp.o \
          build/cursor.cpp.o \
          build/video_sequence.cpp.o \
          build/config_linux.cpp.o
## Headers:
HEADERS = src/main.hpp \
          src/globals.hpp \
          src/game.hpp \
          src/padding_data_calculator.hpp \
          src/cursor.hpp \
          src/video_sequence.hpp \
          src/config.hpp \
          src/config_linux.hpp \
          src/config_windows.hpp \
          src/config_common.hpp
## Libs:
LIBS = sfml-window sfml-graphics sfml-system libavcodec libavformat
## Compiler-Flags:
CFLAGS = -c `pkg-config $(LIBS) --cflags`
## Linker-Flags:
LFLAGS = `pkg-config $(LIBS) --libs`

### TARGETS
## link all:
all: $(TARGET)
## link elf executable:
$(TARGET): $(OBJECTS)
	g++ -o $@ $(OBJECTS) $(LFLAGS)
## compile src/*.cpp to build/*.o:
build/%.cpp.o : src/%.cpp $(HEADERS)
	g++ $< -o $@ $(CFLAGS)
