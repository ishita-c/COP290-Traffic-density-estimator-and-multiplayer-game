OBJS = $(patsubst code/%.cpp,build/%.o,$(wildcard code/*.cpp))
LDFLAGS = $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm -lenet
DEPENDS = $(OBJS:.o=.d)

.SUFFIXES: .cpp .o

all: mario-bros

mario-bros: $(OBJS)
	g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Wformat=2 -Wstrict-aliasing=2 -MMD $^ $(LDFLAGS) -o $@

build/%.o: code/%.cpp
	mkdir -p build
	g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Wformat=2 -Wstrict-aliasing=2 -MMD -c $< $(LDFLAGS) -o $@

clean:
	-rm -rf build mario-bros

-include $(DEPENDS)
