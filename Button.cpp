#include "Button.hpp"

Button::Button(Vector2f st, Vector2f fn, Color c):VisualComponent(st, fn)
{
  _body.setFillColor(c);
  _body.setPosition(VisualComponent::GetPosition());
  _body.setSize(VisualComponent::GetSize());
}

void Button::DrawTo(RenderWindow &w)
{
  w.draw(_body);
}

void Button::OnClick()
{
}

void Button::ReSize(Vector2f s)
{
  VisualComponent::ReSize(s);
  _body.setSize(VisualComponent::GetSize());
}
