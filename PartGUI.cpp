#include "PartGUI.hpp"

void PartGUI::SetPosition(Vector2f p)
{
  _p = p;
}

bool PartGUI::isMouseOver(RenderWindow &w)
{
  int mouseX = Mouse::getPosition(w).x;
  int mouseY = Mouse::getPosition(w).y;

  if (mouseX < _p.x + _w && mouseX > _p.x && mouseY < _p.y + _h && mouseY > _p.y) 
    return true;
  
  return false;
}

PartGUI::PartGUI(Vector2f p, Uint32 h, Uint32 w):_p(p), _h(h), _w(w)
{
}