#include "BorderDecor.hpp"

BorderDecor::BorderDecor(VisualComponent *vc, Uint32 w, Color c) : Decorator(vc), _widht(w)
{
  _entity.setFillColor(Color::Transparent);
  _entity.setOutlineColor(c);
  _entity.setOutlineThickness(w);
  _entity.setPosition(vc->GetPosition());
  _entity.setSize(vc->GetSize());
}

void BorderDecor::DrawTo(RenderWindow &w)
{
  _entity.setPosition(Decorator::GetPosition());
  _entity.setSize(Decorator::GetSize());
  w.draw(_entity);
  Decorator::DrawTo(w);
}

void BorderDecor::ReSize(Vector2f s)
{
  Decorator::ReSize(s);
  _entity.setSize(Decorator::GetSize());
}