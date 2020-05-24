#include "InputBox.hpp"

InputBox::InputBox(Vector2f st, Vector2f fn, Font &font, Color tc, Color bgc, Int32 chs):VisualComponent(st,fn)
{
  _body.setCharacterSize(chs);
  _body.setFillColor(bgc);
  _body.setColor(tc);
  _body.setFont(font);
}

void InputBox::DrawTo(RenderWindow &w)
{
  w.draw(_body);
}

void InputBox::OnClick()
{
  _select = true;
}

bool InputBox::isMouseOver(RenderWindow &w)
{
  bool res = VisualComponent::isMouseOver(w);
  if(!res)
    _select = false;
  return res;
}

void InputBox::Record(Event &e)
{
  if(_select)
  {
    
  }
}