#include "CheckBox.hpp"

CheckBox::CheckBox(Vector2f st,  Texture &yes, Texture &no): VisualComponent(st, {0,0})
{
  _yes = &yes;
  _no = &no;
  _value = false;
  _body.setTexture(*_no);
  _body.setPosition(st);
  VisualComponent::ReSize({_body.getLocalBounds().width, _body.getLocalBounds().height});
}

void CheckBox::DrawTo(RenderWindow &w)
{
  w.draw(_body);
}

void CheckBox::OnClick()
{
  _value = !_value ;
  _body.setTexture(_value?*_yes:*_no);
}

string CheckBox::GetValue()
{
  return _value?"Y":"N";
}

VisualComponent *CheckBox::SetValue(string s)
{
  if(s=="Y")
    _value = true;
  else
    _value = false;
  _body.setTexture(_value?*_yes:*_no);
  return this;
}