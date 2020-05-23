CC=g++
CFLAGS= -g3 -c -Wall -std=c++1z 

SOURCES= client.cpp User.cpp

BUILDDIR  = obj/
DIR = /home/artem/TicTacToe
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=TicTacToe.out

all: $(SOURCES) $(EXECUTABLE)
	$(CC) server.cpp $(CFLAGS) -o ServerTTT.out $(CFLAGS)-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network 
	rm -rf *.o 

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
