CC=g++
CFLAGS= -g3 -c -Wall -std=c++1z 

SOURCES= User.cpp ExPacket.cpp BorderDecor.cpp Button.cpp Decorator.cpp VisualComponent.cpp HeaderDecor.cpp InputBox.cpp BackGroundDecor.cpp OutputBox.cpp Field.cpp WindowTTT.cpp WindowTTTBuilder.cpp CheckBox.cpp main.cpp

BUILDDIR  = obj/
DIR = /home/artem/TicTacToe
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=TicTacToe.out

all: $(SOURCES) $(EXECUTABLE)
	$(CC) server.cpp $(CFLAGS) -o ServerTTT.out $(CFLAGS)-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -pthread
	rm -rf *.o 

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
