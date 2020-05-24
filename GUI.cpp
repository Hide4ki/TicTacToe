#include "GUI.hpp"

void GUI::RunConnectWin(string &port, string &ip)
{
  RenderWindow window;

	window.create(VideoMode(500,230), "Connect", Style::Titlebar | Style::Close);

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
        {
					ip += textBoxIp.GetText();
          port += textBoxPort.GetText();
          window.close();
        }
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
}



void GUI::RunLoginWin(string &login, string &pass)
{
  RenderWindow window;

	window.create(VideoMode(500,230), "Login", Style::Titlebar | Style::Close);

	Font font;
	if (!font.loadFromFile("arial.ttf"))
		cout << "Font not found!\n";

	TextBox textBoxLogin({5, 40}, 65, 20);
	textBoxLogin.SetFont(font);
  textBoxLogin.SetColor(Color::Black);
  textBoxLogin.SetSelected(true);
  textBoxLogin.SetLimit(22);
  textBoxLogin.SetHeader("Enter Login");
	Button bottonBox({5, 175}, 75, 25);
  bottonBox.SetText("Confirm");
  bottonBox.SetTextSize(20);
  bottonBox.SetFont(font);
  bottonBox.SetBackColor(Color::Black);
  bottonBox.SetTextColor(Color::White);
  TextBox textBoxPass({5, 125}, 65, 20);
	textBoxPass.SetFont(font);
  textBoxPass.SetColor(Color::Black);
  textBoxPass.SetSelected(false);
  textBoxPass.SetLimit(22);
  textBoxPass.SetHeader("Enter Password");
  BG bg(Color::White);
  Texture t;
  t.loadFromFile("yes.png");

  Texture t2;
  t2.loadFromFile("x.png");
  Sprite s;
  s.setTexture(t);
  s.setPosition({405, 175});
  Text record;
  record.setString("Try sign up=>");
  record.setPosition(200, 175);
  record.setColor(Color::Black);
  record.setFont(font);
  bool tmp = false;
	while (window.isOpen()) 
  {
    Event Event;
    int mouseX = Mouse::getPosition(window).x;
    int mouseY = Mouse::getPosition(window).y;
		while (window.pollEvent(Event)) 
    {
			switch (Event.type) 
      {
			case Event::Closed:
				window.close();
        break;
      case Event::TextEntered:
        textBoxLogin.Reseive(Event);
        textBoxPass.Reseive(Event);
        break;
			case Event::MouseMoved:
				break;
			case Event::MouseButtonPressed:
        if (mouseX < s.getPosition().x + 32 && mouseX > s.getPosition().x && s.getPosition().y  + 32 && mouseY > s.getPosition().y) 
        if(tmp)
        {
          s.setTexture(t2);
          tmp = false;
        }
        else 
        {
          s.setTexture(t);
          tmp = true;
        }
        if (textBoxLogin.isMouseOver(window))
          textBoxLogin.SetSelected(true);
        else
          textBoxLogin.SetSelected(false);
        
        if (textBoxPass.isMouseOver(window))
          textBoxPass.SetSelected(true);
        else
          textBoxPass.SetSelected(false);

				if (bottonBox.isMouseOver(window)) 
        {
					login += textBoxLogin.GetText();
          pass += textBoxPass.GetText();
          window.close();
        }
        break;
			}
		}
		window.clear();
    bg.DrawTo(window);
		textBoxLogin.DrawTo(window);
		textBoxPass.DrawTo(window);
		bottonBox.DrawTo(window);
    window.draw(s);
    window.draw(record);
		window.display();
  }
}