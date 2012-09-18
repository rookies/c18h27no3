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
