#include "OutputBox.hpp"

OutputBox::OutputBox(Vector2f st, Vector2f fn, Font &font, Color c, Int32 chs) : VisualComponent(st, fn)
{
  _body.setCharacterSize(chs);
  _body.setColor(c);
  _body.setFont(font);
  _body.setPosition(st);
  _fnStatic = fn - st;
}

void OutputBox::DrawTo(RenderWindow &w)
{
  w.draw(_body);
}

void OutputBox::OnClick()
{

}

string OutputBox::GetValue()
{
  return _body.getString();
}

void OutputBox::SetValue(string s)
{
  _body.setString(s);

  if(_body.getLocalBounds().height > VisualComponent::GetSize().y )
    VisualComponent::ReSize({VisualComponent::GetSize().x, _body.getLocalBounds().height});

  if(_fnStatic.x + 5 < VisualComponent::GetSize().x)
    VisualComponent::ReSize({_fnStatic.x + 5, VisualComponent::GetSize().y});

 if(_body.getLocalBounds().width + 5 > VisualComponent::GetSize().x)
    VisualComponent::ReSize({_body.getLocalBounds().width + 5, VisualComponent::GetSize().y});
}