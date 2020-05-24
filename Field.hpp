#pragma once

#include "PartGUI.hpp"

const int px = 32;

class Field : public PartGUI
{
public:
  Field(Vector2f, Uint32, Uint32);
  void DrawTo(RenderWindow &) override;
  virtual ~Field(); 
private:
  Texture _free;
  Texture _o;
  Texture _x;
  Uint32 _yCell;
  Uint32 _xCell;
  int **_grid;
};