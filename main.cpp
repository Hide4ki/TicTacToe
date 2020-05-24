#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextBox.hpp"
#include "Button.hpp"
#include "Field.hpp"

using namespace std;
using namespace sf;

int main() 
{
	RenderWindow window;

	Vector2i centerWindow((VideoMode::getDesktopMode().width / 2) - 445, (VideoMode::getDesktopMode().height / 2) - 480);

	window.create(VideoMode(900, 900), "SFML Textbox", Style::Titlebar | Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	Font font;
	if (!font.loadFromFile("arial.ttf"))
		cout << "Font not found!\n";

	TextBox text1({ 100, 100 }, 23,21, 20, Color::White, true);
	text1.SetLimit(true, 30);
	text1.SetFont(font);

	Button btn1("Enter",{ 300, 100}, { 200, 100 }, 30, Color::Green, Color::Black);
	btn1.SetFont(font);
	
  Field f({0,0},5,5);

	//Main Loop:
	while (window.isOpen()) 
  {

    Event Event;

		while (window.pollEvent(Event)) 
    {
			switch (Event.type) 
      {

			case Event::Closed:
				window.close();
			case Event::TextEntered:
				text1.Reseive(Event);
			case Event::MouseMoved:
				if (btn1.isMouseOver(window)) 
					btn1.SetBackColor(Color::Magenta);
				else 
          btn1.SetBackColor(Color::Green);
				break;
			case Event::MouseButtonPressed:;
				if (btn1.isMouseOver(window)) {
					std::cout << "Hello " << text1.GetText() << "\n";
				}
			}
		}
		window.clear();
    f.DrawTo(window);
		//text1.DrawTo(window);
		//btn1.DrawTo(window);
		window.display();
	}
}