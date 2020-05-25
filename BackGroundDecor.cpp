#include "BackGroundDecor.hpp"

BackGroundDecor::BackGroundDecor(VisualComponent *vc, Color c) : Decorator(vc)
{
  _body.setFillColor(c);
}

void BackGroundDecor::DrawTo(RenderWindow &w)
{
  _body.setPosition(Decorator::GetPosition() - Vector2f{10,10});
  _body.setSize(Decorator::GetSize() + Vector2f{30,30});
  w.draw(_body);
  Decorator::DrawTo(w);
}

Vector2f BackGroundDecor::GetPosition()
{
  return Decorator::GetPosition() - Vector2f(10,10);
}

Vector2f BackGroundDecor::GetSize()
{
  return Decorator::GetSize() + Vector2f(30,30);
}