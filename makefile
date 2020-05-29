CC=g++
CFLAGS= -g3 -c -Wall -std=c++1z 

SOURCES=main.cpp ExPacket.cpp BorderDecor.cpp  Button.cpp Decorator.cpp VisualComponent.cpp HeaderDecor.cpp InputBox.cpp BackGroundDecor.cpp OutputBox.cpp Field.cpp WindowTTT.cpp WindowTTTBuilder.cpp CheckBox.cpp MyException.cpp

BUILDDIR  = obj/
DIR = /home/artem/TicTacToe
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=TicTacToe.out

all: $(SOURCES) $(EXECUTABLE)
	$(CC) mainServer.cpp Server.cpp MyException.cpp BorderDecor.cpp  Button.cpp Decorator.cpp VisualComponent.cpp HeaderDecor.cpp InputBox.cpp BackGroundDecor.cpp OutputBox.cpp Field.cpp  WindowTTTBuilder.cpp WindowTTT.cpp User.cpp CheckBox.cpp ExPacket.cpp -std=c++1z -g3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
	rm -rf *.o 

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
