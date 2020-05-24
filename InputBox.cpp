#include "InputBox.hpp"
#include "Key.hpp"

InputBox::InputBox(Vector2f st, Vector2f fn, Font &font, Color tc, Color bgc, Int32 chs, Int32 l):VisualComponent(st,fn), _limit(l)
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
  _body.setString(_cout + "_");
}

bool InputBox::isMouseOver(RenderWindow &w)
{
  bool res = VisualComponent::isMouseOver(w);
  if(!res)
  {
    _select = false;
    _body.setString(_cout);
  }
  return res;
}

void InputBox::Record(Event &e)
{
  if(_select)
  {
    Uint32 ch = e.text.unicode;

    if(ch < 128)
      Enter(ch);  
  }
}

void InputBox::Enter(Uint32 ch)
{
  if(ch == static_cast<Uint32>(Key::DELETE_KEY) && _cout.length() > 0)
  {
    _cout.pop_back();
  }
  else if(ch == static_cast<Uint32>(Key::ESCAPE_KEY))
  {
  }
  else if(ch == static_cast<Uint32>(Key::ENTER_KEY))
  {
  }
  else if(((_limit < 0 || _limit > _cout.length())) && ch>=' ')
    _cout += ch;

  _body.setString(_cout + "_");
}