#include "HeaderDecor.hpp"


HeaderDecor::HeaderDecor(VisualComponent *vc, string s, Font &f, Vector2f offset, Color c, Int32 cs, bool in, bool center):Decorator(vc), _in(in), _center(center)
{
  _body.setFont(f);
  _body.setFillColor(c);
  _body.setString(s);
  _body.setCharacterSize(cs);
  _body.setPosition(Decorator::GetPosition() + offset);
  InComponent();
  Center();
}

void HeaderDecor::DrawTo(RenderWindow &w)
{
  Decorator::DrawTo(w);
  w.draw(_body);
}

void HeaderDecor::ReSize(Vector2f s)
{
  Decorator::ReSize(s);
  InComponent();
}

void HeaderDecor::InComponent()
{
  if(_in)
  {
    if(_body.getLocalBounds().height + 10 > Decorator::GetSize().y)
      Decorator::ReSize({Decorator::GetSize().x, _body.getLocalBounds().height + 10});

    if(_body.getLocalBounds().width + 10 > Decorator::GetSize().x)
      Decorator::ReSize({_body.getLocalBounds().width + 10, Decorator::GetSize().y});

    if(_body.getPosition().x < Decorator::GetPosition().x - 5)
      _body.setPosition({Decorator::GetPosition().x + 5, _body.getPosition().y});

    if(_body.getPosition().y < Decorator::GetPosition().y - 5)
      _body.setPosition({_body.getPosition().x, Decorator::GetPosition().y + 5});

    if(_body.getLocalBounds().height + _body.getPosition().y + 5 > Decorator::GetSize().y + Decorator::GetPosition().y)
      _body.setPosition({_body.getPosition().x, Decorator::GetPosition().y + Decorator::GetSize().y - _body.getLocalBounds().height - 10});

    if(_body.getLocalBounds().width + _body.getPosition().x + 5 > Decorator::GetSize().x + Decorator::GetPosition().x)
      _body.setPosition({Decorator::GetPosition().x + Decorator::GetSize().x - _body.getLocalBounds().width - 5, _body.getPosition().y});

  }
}

void HeaderDecor::Center()
{
  if(_center)
  {
    _body.setPosition({Decorator::GetPosition().x + Decorator::GetSize().x/2 - _body.getLocalBounds().width/2, Decorator::GetPosition().y + Decorator::GetSize().y/2 - _body.getLocalBounds().height/2-5});
  }
}