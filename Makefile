CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=gltestlib1.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=gltestlib1.a
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(LIBRARY)
	$(CC) $(LDFLAGS) main.cpp gltestlib1.a -o $@

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(LIBRARY) $(EXECUTABLE)
