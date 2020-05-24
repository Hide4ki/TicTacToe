#pragma once

#include "Decorator.hpp"

class BorderDecor : public Decorator
{
public:
  BorderDecor(VisualComponent*, Uint32, Color);
  void DrawTo(RenderWindow&) override;
  void ReSize(Vector2f) override;
private:
  Uint32 _widht;
  RectangleShape _entity;
};