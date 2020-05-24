#include "Button.hpp"

Button::Button(Vector2f p, Uint32 h, Uint32 w):PartGUI(p, w, h)
{
  _button.setSize({h,w});
  SetPosition(p);
}

void Button::SetFont(Font &fonts)
{
	_text.setFont(fonts);
}

void Button::SetText(string s)
{
  _text.setString(s);
}

void Button::SetBackColor(Color color)
{
  _button.setFillColor(color);
}

void Button::SetTextColor(Color color)
{
  _text.setColor(color);
}

void Button::SetTextSize(Uint32 s)
{
  _text.setCharacterSize(s);
}

void Button::SetPosition(Vector2f p)
{
	_button.setPosition(p);
  _text.setPosition(p);
}

void Button::DrawTo(RenderWindow &w)
{
  w.draw(_button);
  w.draw(_text);
}

void Button::AddBox(TextBox *tb)
{
  _linkBoxs.push_back(tb);
}
