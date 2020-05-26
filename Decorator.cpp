#include "Decorator.hpp"

Decorator::Decorator(VisualComponent *c):_component(c)
{
}
 
void Decorator::DrawTo(RenderWindow &w)
{
  _component->DrawTo(w);
}

bool Decorator::isMouseOver(RenderWindow &w)
{
  return _component->isMouseOver(w);
}

void Decorator::OnClick()
{
  _component->OnClick();
}

Vector2f Decorator::GetPosition()
{
  return _component->GetPosition();
}

Vector2f Decorator::GetSize()
{
  return _component->GetSize();
}

void Decorator::ReSize(Vector2f s)
{
  _component->ReSize(s);
}

Decorator::~Decorator()
{
  delete _component;
}

string Decorator::GetValue()
{
  return _component->GetValue();
}

VisualComponent *Decorator::SetValue(string s) 
{
  _component->SetValue(s);
  return this;
}

void Decorator::AddCh(Event &e)
{
  _component->AddCh(e);
}


