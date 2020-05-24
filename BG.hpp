#pragma once

#include <SFML/Graphics.hpp>
#include "PartGUI.hpp"

using namespace std;
using namespace sf;

class BG : public PartGUI
{
public:
  BG(Color c):PartGUI({0,0}, VideoMode::getDesktopMode().height,VideoMode::getDesktopMode().width)
  { 
    _rect.setSize({VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height});
    _rect.setFillColor(c);
  };
  void DrawTo(RenderWindow &w)
  {
    w.draw(_rect);
  }
private:
  RectangleShape _rect;
};