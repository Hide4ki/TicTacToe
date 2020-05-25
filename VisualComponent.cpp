#include "VisualComponent.hpp"

VisualComponent::VisualComponent(Vector2f st, Vector2f fn):_st(st),_fn(fn)
{
}

bool VisualComponent::isMouseOver(RenderWindow &w)
{
  Uint32 mouseX = Mouse::getPosition(w).x;
  Uint32 mouseY = Mouse::getPosition(w).y;

  if (mouseX < _fn.x && mouseX > _st.x && mouseY < _fn.y && mouseY > _st.y) 
    return true;
  
  return false;
}

Vector2f VisualComponent::GetPosition()
{
  return _st;
}

Vector2f VisualComponent::GetSize()
{
  return _fn - _st;
}

void VisualComponent::ReSize(Vector2f s)
{ 
  _fn -= GetSize() - s;
}


string VisualComponent::GetValue()
{
  return "";
}

void VisualComponent::SetValue(string)
{

}

void VisualComponent::AddCh(Event&)
{

}


