CC=g++
CFLAGS= -g3 -c -Wall -std=c++11 

SOURCES=main.cpp

BUILDDIR  = obj/
DIR = /home/art em/TicTacToe
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=TicTacToe.out

all: $(SOURCES) $(EXECUTABLE)
	rm -rf *.o 

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
			all