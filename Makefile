OBJ=$(patsubst %.cpp,%.o,$(wildcard source/*.cpp))
OBJ_=$(wildcard *.o)
CFLAGS= -std=c++11 -O2 `pkg-config opencv4 --cflags` -DNO_SCREEN_GRAB
LDFLAGS= `pkg-config opencv4 --libs`

source/%.o: source/%.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

libacidcam: $(OBJ)
	$(CXX) -std=c++11  -shared -o libacidcam.dylib $(OBJ)  $(LDFLAGS)

all: libacidcam


.PHONY: clean
clean:
	rm -f source/*.o *.dylib
