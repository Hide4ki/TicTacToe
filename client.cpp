#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextBox.hpp"
#include "Button.hpp"
#include "BG.hpp"
#include "Field.hpp"


using namespace std;
using namespace sf;

int main() 
{
  RenderWindow window;

	window.create(VideoMode(500,230), "Connect Test", Style::Titlebar | Style::Close);

	Font font;
	if (!font.loadFromFile("arial.ttf"))
		cout << "Font not found!\n";

	TextBox textBoxIp({5, 40}, 65, 20);
	textBoxIp.SetFont(font);
  textBoxIp.SetColor(Color::Black);
  textBoxIp.SetSelected(true);
  textBoxIp.SetLimit(22);
  textBoxIp.SetHeader("Enter IP");
	Button bottonBox({5, 175}, 75, 25);
  bottonBox.SetText("Confirm");
  bottonBox.SetTextSize(20);
  bottonBox.SetFont(font);
  bottonBox.SetBackColor(Color::Black);
  bottonBox.SetTextColor(Color::White);
  TextBox textBoxPort({5, 125}, 65, 20);
	textBoxPort.SetFont(font);
  textBoxPort.SetColor(Color::Black);
  textBoxPort.SetSelected(false);
  textBoxPort.SetLimit(22);
  textBoxPort.SetHeader("Enter Port");
  BG bg(Color::White);
	while (window.isOpen()) 
  {
    Event Event;

		while (window.pollEvent(Event)) 
    {
			switch (Event.type) 
      {
			case Event::Closed:
				window.close();
        break;
      case Event::TextEntered:
        textBoxIp.Reseive(Event);
        textBoxPort.Reseive(Event);
        break;
			case Event::MouseMoved:
				break;
			case Event::MouseButtonPressed:
        if (textBoxIp.isMouseOver(window))
          textBoxIp.SetSelected(true);
        else
          textBoxIp.SetSelected(false);
        
        if (textBoxPort.isMouseOver(window))
          textBoxPort.SetSelected(true);
        else
          textBoxPort.SetSelected(false);

				if (bottonBox.isMouseOver(window)) 
					std::cout << "Hello " << textBoxIp.GetText() << "\n";
        break;
			}
		}
		window.clear();
    bg.DrawTo(window);
		textBoxIp.DrawTo(window);
		textBoxPort.DrawTo(window);
		bottonBox.DrawTo(window);
		window.display();
  }
  return 0;
}