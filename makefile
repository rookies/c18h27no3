### OPTIONS
## Target:
TARGET = game
## Object-Files:
OBJECTS = build/main.o \
          build/padding_data_calculator.o \
          build/game.o \
          build/video_sequence.o \
          build/cursor.o
## Headers:
HEADERS = src/main.h \
          src/globals.h \
          src/padding_data_calculator.h \
          src/game.h \
          src/video_sequence.h \
          src/cursor.h
## Libs:
LIBS = sdl SDL_image SDL_gfx libavformat libavcodec
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
build/%.o : src/%.cpp $(HEADERS)
	g++ $< -o $@ $(CFLAGS)
