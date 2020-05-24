#include <string>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BorderDecor.hpp"
#include "Button.hpp"
#include "HeaderDecor.hpp"
#include "InputBox.hpp"

using namespace std;
using namespace sf;

int main() 
{
	Font font;
	if (!font.loadFromFile("arial.ttf"))
		cout << "Font not found!\n";  
  RenderWindow Window(VideoMode(500, 500, 32), "Test");
  Button *newB = new Button({120,120}, {330,210}, Color::White);
  BorderDecor *newElem = new BorderDecor(newB, 3, Color::Red);
  HeaderDecor *tmp = new HeaderDecor(newElem, "Hello World", font, {0, 0}, Color::Black, 20, true, true);
  InputBox box({10,10}, {200,130}, font, Color::Green, Color::Red, 20, 25);
  while(Window.isOpen()) {
    Event event;
   
    while (Window.pollEvent(event)) 
    {
        switch (event.type) {
        case Event::Closed:
          Window.close();
          break;
        case Event::KeyPressed:
          break;
        case Event::TextEntered:
          box.Record(event);
          break;
        case Event::MouseButtonPressed:
          if(box.isMouseOver(Window))
            box.OnClick();
          if(tmp->isMouseOver(Window))
            tmp->OnClick();  
          break;
        }
    }
 
    Window.clear();
    box.DrawTo(Window);
    tmp->DrawTo(Window);
    Window.display();
  }
  delete tmp;
  return 0;
}