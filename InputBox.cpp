#include "InputBox.hpp"

InputBox::InputBox(Vector2f st, Vector2f fn, Font &font, Color tc,  Int32 chs, Int32 l):VisualComponent(st,fn), _limit(l)
{
  _body.setCharacterSize(chs);
  _body.setFillColor(tc);
  _body.setFont(font);
  _body.setPosition(st);
  _fnStatic = fn - st;
}

void InputBox::DrawTo(RenderWindow &w)
{
  w.draw(_body);
}

void InputBox::OnClick()
{
  _select = true;
  SetValue(_limit != _cout.length()?_cout + "_":_cout);
}

bool InputBox::isMouseOver(RenderWindow &w)
{
  bool res = VisualComponent::isMouseOver(w);
  if(!res)
  {
    _select = false;
    SetValue(_cout);
  }
  return res;
}

void InputBox::AddCh(Event &e)
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
  else if(((_limit < 0 || _limit > _cout.length())) && (ch=='.' || (ch >= '0' && ch <= '9')))
    _cout += ch;
  SetValue(_limit != _cout.length()?_cout + "_":_cout);
}


VisualComponent *InputBox::SetValue(string val)
{
  _body.setString(val);

  if(_body.getLocalBounds().height > VisualComponent::GetSize().y )
    VisualComponent::ReSize({VisualComponent::GetSize().x, _body.getLocalBounds().height});
    
  if(_fnStatic.x + 5 < VisualComponent::GetSize().x)
    VisualComponent::ReSize({_fnStatic.x + 5, VisualComponent::GetSize().y});

  if(_body.getLocalBounds().width + 5 > VisualComponent::GetSize().x)
    VisualComponent::ReSize({_body.getLocalBounds().width + 5, VisualComponent::GetSize().y});
  return this;
}

string InputBox::GetValue()
{
  auto tmp = _body.getString();
  return tmp==""?"0":tmp;
}