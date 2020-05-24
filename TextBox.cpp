#include "TextBox.hpp"

TextBox::TextBox(Vector2f p, Uint32 w, Uint32 h):PartGUI(p, h, w)
{
  _textbox.setPosition(_p);
  _border.setPosition(_p);
  _border.setOutlineThickness(2 );
  _border.setOutlineColor(Color::Black);
  _header.setString("");
  _header.setPosition(_p);
  _header.setColor(Color::Black);
}

void TextBox::SetFont(Font &f)
{
  _textbox.setFont(f);
  _header.setFont(f);
}

void TextBox::SetPosition(Vector2f p)
{
  _textbox.setPosition(p);
}

string TextBox::GetText() 
{
  return _text.str();
}

void TextBox::DrawTo(RenderWindow &w)
{
  w.draw(_border);
  w.draw(_header);
  w.draw(_textbox);
}

void TextBox::SetColor(Color c)
{
  _textbox.setFillColor(c);
}

void TextBox::Reseive(Event input)
{
  if(_isSelected)
  {
    Uint32 chType = input.text.unicode;

    if(chType < 128)
    {
      if(_limit >= 0)
      {
        if(_text.str().length() <= _limit)
          SpecRead(chType);
        else if(chType == static_cast<Uint32>(Key::DELETE_KEY))
          DeleteLast();
      }
      else
        SpecRead(chType);
    }
  }
}

void TextBox::DeleteLast()
{
  string t = _text.str();
  string newT = "";
  for (int i = 0; i < t.length() - 1; i++) 
    newT += t[i];
  _text.str("");
  _text << newT;
  _textbox.setString(_text.str() + "_");
}

void TextBox::SpecRead(Uint32 t)
{
  if (t != static_cast<Uint32>(Key::DELETE_KEY) && t != static_cast<Uint32>(Key::ENTER_KEY) && t != static_cast<Uint32>(Key::ESCAPE_KEY)) 
    _text << static_cast<char>(t);
  else if (t == static_cast<Uint32>(Key::DELETE_KEY)) 
    if (_text.str().length() > 0) 
      DeleteLast();
  _textbox.setString(_text.str() + "_");
}

void TextBox::SetSelected(bool s)
{
  _isSelected = s;
}

void TextBox::SetLimit(Uint32 l)
{
  _limit = l;
  _border.setSize({l*20,_h+20});
}

bool TextBox::isMouseOver(RenderWindow &w) 
{
  int mouseX = Mouse::getPosition(w).x;
  int mouseY = Mouse::getPosition(w).y;

  if (mouseX < _p.x + _border.getSize().x && mouseX > _p.x && mouseY < _p.y + _border.getSize().y && mouseY > _p.y) 
    return true;
  
  return false;
}

void TextBox::SetHeader(string h)
{
  _header.setString(h);
  _header.setPosition({_p.x,_p.y - 35});
}