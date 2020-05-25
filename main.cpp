#include <string>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BorderDecor.hpp"
#include "Button.hpp"
#include "HeaderDecor.hpp"
#include "InputBox.hpp"
#include "BackGroundDecor.hpp"
#include "OutputBox.hpp"

using namespace std;
using namespace sf;

int main() 
{
	Font font;
	if (!font.loadFromFile("arial.ttf"))
		cout << "Font not found!\n";  
  RenderWindow Window(VideoMode(500, 500, 32), "Test");
  Button *newB = new Button({10,200}, {330,250}, Color::White);
  BorderDecor *newElem = new BorderDecor(newB, 3, Color::Red);
  HeaderDecor *tmp = new HeaderDecor(newElem, "Hello World", font, {0, 0}, Color::Black, 20, true, true);
  InputBox *box = new InputBox({30,30}, {200,130}, font, Color::Green, 20, 25);
  BackGroundDecor *bg = new BackGroundDecor(box, Color::White);
  BorderDecor *BD = new BorderDecor(bg, 3, Color::Red);
  OutputBox *og = new OutputBox({30,330}, {200,380}, font, Color::Green, 20);
  BackGroundDecor *bg2 = new BackGroundDecor(og, Color::White);
  BorderDecor *BD2 = new BorderDecor(bg2, 3, Color::Red);
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
          BD->AddCh(event);
          break;
        case Event::MouseButtonPressed:
          if(BD->isMouseOver(Window))
            BD->OnClick();
          if(tmp->isMouseOver(Window))
          {
            tmp->OnClick();  
            BD2->SetValue("You enter:" + BD->GetValue());
          }
          break;
        }
    }
 
    Window.clear();
    BD->DrawTo(Window);
    tmp->DrawTo(Window);
    BD2->DrawTo(Window);
    Window.display();
  }
  delete tmp;
  delete BD2;
  delete BD;
  return 0;
}