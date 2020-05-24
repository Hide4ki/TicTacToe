#pragma once

#include <SFML/Graphics.hpp>
#include "Key.hpp"

using namespace std;
using namespace sf;

class PartGUI
{
public:
  PartGUI() = delete;
  PartGUI(const PartGUI&) = delete;
  PartGUI(PartGUI&&) = delete;
  virtual ~PartGUI() = default;
  virtual void DrawTo(RenderWindow &) = 0;
  virtual void SetPosition(Vector2f);
  virtual bool isMouseOver(RenderWindow &);
protected:
  PartGUI(Vector2f, Uint32, Uint32);
  Uint32 _h;
  Uint32 _w;
  Vector2f _p;
};